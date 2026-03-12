#include "MetalRenderEncoder.hpp"
#include "MetalRenderContext.hpp"
#include "MetalTextureView.hpp"
#include "MetalBuffer.hpp"
#include "MetalRenderPipeline.hpp"
#include "MetalDevice.hpp"

#include <Termina/Core/Logger.hpp>
#include <MetalShaderConverter/metal_irconverter_runtime.h>

namespace Termina {
    MetalRenderEncoder::MetalRenderEncoder(MetalRenderContext* ctx, const RenderEncoderInfo& info)
        : m_ParentCtx(ctx)
    {
        MTLRenderPassDescriptor* descriptor = [MTLRenderPassDescriptor renderPassDescriptor];
        for (uint64 i = 0; i < info.ColorAttachments.size(); i++) {
            descriptor.colorAttachments[i].texture = reinterpret_cast<MetalTextureView*>(info.ColorAttachments[i])->GetView();
            descriptor.colorAttachments[i].loadAction = info.ColorClearFlags[i] ? MTLLoadActionClear : MTLLoadActionLoad;
            descriptor.colorAttachments[i].clearColor = MTLClearColorMake(info.ColorClearValues[i].r, info.ColorClearValues[i].g, info.ColorClearValues[i].b, info.ColorClearValues[i].a);
            descriptor.colorAttachments[i].storeAction = MTLStoreActionStore;
        }
        if (info.DepthAttachment) {
            descriptor.depthAttachment.texture = reinterpret_cast<MetalTextureView*>(info.DepthAttachment)->GetView();
            descriptor.depthAttachment.loadAction = info.DepthClearFlag ? MTLLoadActionClear : MTLLoadActionLoad;
            descriptor.depthAttachment.clearDepth = 1.0f;
            descriptor.depthAttachment.storeAction = info.DepthStoreFlag ? MTLStoreActionStore : MTLStoreActionDontCare;
        }
        descriptor.renderTargetWidth = info.Width;
        descriptor.renderTargetHeight = info.Height;

        m_Encoder = [ctx->GetCommandBuffer() renderCommandEncoderWithDescriptor:descriptor];
        m_Encoder.label = info.Name.empty() ? @"Render Pass" : [NSString stringWithUTF8String:info.Name.c_str()];
    }

    void MetalRenderEncoder::SetViewport(float x, float y, float width, float height)
    {
        MTLViewport viewport;
        viewport.originX = x;
        viewport.originY = y;
        viewport.width = width;
        viewport.height = height;
        viewport.znear = 0.0f;
        viewport.zfar = 1.0f;

        [m_Encoder setViewport:viewport];
    }

    void MetalRenderEncoder::SetScissorRect(int left, int top, int right, int bottom)
    {
        MTLScissorRect rect;
        rect.x = left;
        rect.y = top;
        rect.width = right - left;
        rect.height = bottom - top;

        [m_Encoder setScissorRect:rect];
    }

    void MetalRenderEncoder::SetPipeline(Pipeline* pipeline)
    {
        m_CurrentPipeline = pipeline;

        MetalDevice* device = m_ParentCtx->GetParentDevice();
        if (pipeline->GetType() == PipelineType::Graphics) {
            MetalRenderPipeline* metalPipeline = static_cast<MetalRenderPipeline*>(pipeline);
            [m_Encoder setRenderPipelineState:metalPipeline->GetPipelineState()];
            [m_Encoder setCullMode:GetMetalCullMode(metalPipeline->GetDesc().CullMode)];
            [m_Encoder setTriangleFillMode:GetMetalFillMode(metalPipeline->GetDesc().FillMode)];
            [m_Encoder setFrontFacingWinding:MTLWindingClockwise];
            if (metalPipeline->GetDesc().DepthReadEnabled || metalPipeline->GetDesc().DepthWriteEnabled) {
                [m_Encoder setDepthStencilState:metalPipeline->GetDepthStencilState()];
            }
            if (metalPipeline->GetDesc().DepthClampEnabled) {
                [m_Encoder setDepthClipMode:MTLDepthClipModeClamp];
            } else {
                [m_Encoder setDepthClipMode:MTLDepthClipModeClip];
            }

            id<MTLBuffer> descriptorHeap = device->GetBindlessManager()->GetHandle();
            [m_Encoder setVertexBuffer:descriptorHeap offset:0 atIndex:kIRDescriptorHeapBindPoint];
            [m_Encoder setFragmentBuffer:descriptorHeap offset:0 atIndex:kIRDescriptorHeapBindPoint];

            id<MTLBuffer> samplerHeap = device->GetBindlessManager()->GetSamplerHandle();
            [m_Encoder setVertexBuffer:samplerHeap offset:0 atIndex:kIRSamplerHeapBindPoint];
            [m_Encoder setFragmentBuffer:samplerHeap offset:0 atIndex:kIRSamplerHeapBindPoint];

            [m_Encoder setVertexBuffer:m_ParentCtx->GetAB()->GetBuffer() offset:0 atIndex:kIRArgumentBufferBindPoint];
            [m_Encoder setFragmentBuffer:m_ParentCtx->GetAB()->GetBuffer() offset:0 atIndex:kIRArgumentBufferBindPoint];
        }
    }

    void MetalRenderEncoder::SetIndexBuffer(RendererBuffer* buffer)
    {
        m_CurrIndexBuffer = (MetalBuffer*)buffer;
    }

    void MetalRenderEncoder::SetConstants(uint32 size, const void* data)
    {
        auto alloc = m_ParentCtx->GetAB()->Alloc(1);
        memcpy(alloc.first, data, size);

        if (alloc.second != 0) {
            [m_Encoder setVertexBufferOffset:alloc.second atIndex:kIRArgumentBufferBindPoint];
            [m_Encoder setFragmentBufferOffset:alloc.second atIndex:kIRArgumentBufferBindPoint];
        }
    }

    void MetalRenderEncoder::Draw(uint32 vertexCount, uint32 instanceCount, uint32 firstVertex, uint32 firstInstance)
    {
        if (m_CurrentPipeline->GetType() != PipelineType::Graphics) TN_ERROR("Can't use draw calls on non graphics pipelines!");
        MetalRenderPipeline* pipeline = (MetalRenderPipeline*)m_CurrentPipeline;

        [m_Encoder drawPrimitives:GetMetalCmdListTopology(pipeline->GetDesc().Topology)
                   vertexStart:firstVertex
                   vertexCount:vertexCount
                   instanceCount:instanceCount
                   baseInstance:firstInstance];
    }

    void MetalRenderEncoder::DrawIndexed(uint32 indexCount, uint32 instanceCount, uint32 firstIndex, int32 vertexOffset, uint32 firstInstance)
    {
        if (m_CurrentPipeline->GetType() != PipelineType::Graphics) TN_ERROR("Can't use draw calls on non graphics pipelines!");
        MetalRenderPipeline* pipeline = (MetalRenderPipeline*)m_CurrentPipeline;

        uint32 stride = m_CurrIndexBuffer->GetDesc().Stride;
        MTLIndexType indexType = stride == 2 ? MTLIndexTypeUInt16 : MTLIndexTypeUInt32;

        [m_Encoder drawIndexedPrimitives:GetMetalCmdListTopology(pipeline->GetDesc().Topology)
                   indexCount:indexCount
                   indexType:indexType
                   indexBuffer:m_CurrIndexBuffer->GetBuffer()
                   indexBufferOffset:firstIndex * stride
                   instanceCount:instanceCount
                   baseVertex:vertexOffset
                   baseInstance:firstInstance];
    }

    void MetalRenderEncoder::End()
    {
        [m_Encoder endEncoding];
        delete this;
    }
} // namespace Termina
