#include "MetalComputeEncoder.hpp"
#include "MetalRenderContext.hpp"
#include "MetalComputePipeline.hpp"
#include "MetalDevice.hpp"

#include <Termina/Core/Logger.hpp>
#include <MetalShaderConverter/metal_irconverter_runtime.h>

namespace Termina {
    MetalComputeEncoder::MetalComputeEncoder(MetalRenderContext* ctx, const std::string& name)
        : m_ParentCtx(ctx)
    {
        m_CommandEncoder = [m_ParentCtx->GetCommandBuffer() computeCommandEncoder];
        m_CommandEncoder.label = [NSString stringWithUTF8String:name.c_str()];
    }

    MetalComputeEncoder::~MetalComputeEncoder()
    {
        [m_CommandEncoder endEncoding];
    }

    void MetalComputeEncoder::SetPipeline(Pipeline* pipeline)
    {
        if (pipeline->GetType() != PipelineType::Compute) TN_ERROR("Cannot bind a non-compute pipeline to a compute encoder!");
        MetalComputePipeline* pipe = static_cast<MetalComputePipeline*>(pipeline);

        MetalDevice* device = m_ParentCtx->GetParentDevice();
        m_CurrentPipeline = pipeline;

        [m_CommandEncoder setComputePipelineState:pipe->GetPipelineState()];

        id<MTLBuffer> descriptorHeap = device->GetBindlessManager()->GetHandle();
        id<MTLBuffer> samplerHeap = device->GetBindlessManager()->GetSamplerHandle();

        [m_CommandEncoder setBuffer:descriptorHeap offset:0 atIndex:kIRDescriptorHeapBindPoint];
        [m_CommandEncoder setBuffer:samplerHeap offset:0 atIndex:kIRSamplerHeapBindPoint];
        [m_CommandEncoder setBuffer:m_ParentCtx->GetAB()->GetBuffer() offset:0 atIndex:kIRArgumentBufferBindPoint];
    }

    void MetalComputeEncoder::SetConstants(uint32 size, const void* data)
    {
        auto alloc = m_ParentCtx->GetAB()->Alloc(1);
        memcpy(alloc.first, data, size);

        if (alloc.second != 0) {
            [m_CommandEncoder setBufferOffset:alloc.second atIndex:kIRArgumentBufferBindPoint];
        }
    }

    void MetalComputeEncoder::Dispatch(uint32 x, uint32 y, uint32 z, uint32 gx, uint32 gy, uint32 gz)
    {
        [m_CommandEncoder dispatchThreads:MTLSizeMake(x, y, z) threadsPerThreadgroup:MTLSizeMake(gx, gy, gz)];
    }

    void MetalComputeEncoder::End()
    {
        [m_CommandEncoder endEncoding];
    }
} // namespace Termina
