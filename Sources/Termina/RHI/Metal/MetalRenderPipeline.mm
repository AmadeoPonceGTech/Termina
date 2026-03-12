#include "MetalRenderPipeline.hpp"
#include "MetalDevice.hpp"
#include "MetalTexture.hpp"

#include <Termina/Core/Logger.hpp>

namespace Termina {
    MetalRenderPipeline::MetalRenderPipeline(MetalDevice* device, const RenderPipelineDesc& desc)
    {
        m_Desc = desc;

        NSError* error = nil;
        dispatch_data_t vertexData = dispatch_data_create(desc.ShaderModules.at(ShaderType::VERTEX).Bytecode.data(),
                                                          desc.ShaderModules.at(ShaderType::VERTEX).Bytecode.size(),
                                                          dispatch_get_main_queue(), NULL);
        id<MTLLibrary> vertexLibrary = [device->GetDevice() newLibraryWithData:vertexData error:&error];

        dispatch_data_t fragmentData = dispatch_data_create(desc.ShaderModules.at(ShaderType::PIXEL).Bytecode.data(),
                                                            desc.ShaderModules.at(ShaderType::PIXEL).Bytecode.size(),
                                                            dispatch_get_main_queue(), NULL);
        id<MTLLibrary> fragmentLibrary = [device->GetDevice() newLibraryWithData:fragmentData error:&error];

        NSString* vertexName = [[NSString alloc] initWithBytes:desc.ShaderModules.at(ShaderType::VERTEX).EntryPoint.c_str()
                                                        length:desc.ShaderModules.at(ShaderType::VERTEX).EntryPoint.size()
                                                      encoding:NSUTF8StringEncoding];
        NSString* fragmentName = [[NSString alloc] initWithBytes:desc.ShaderModules.at(ShaderType::PIXEL).EntryPoint.c_str()
                                                          length:desc.ShaderModules.at(ShaderType::PIXEL).EntryPoint.size()
                                                        encoding:NSUTF8StringEncoding];

        id<MTLFunction> vertexFunction = [vertexLibrary newFunctionWithName:vertexName];
        id<MTLFunction> fragmentFunction = [fragmentLibrary newFunctionWithName:fragmentName];

        MTLRenderPipelineDescriptor* pipelineDescriptor = [MTLRenderPipelineDescriptor new];
        pipelineDescriptor.vertexFunction = vertexFunction;
        pipelineDescriptor.fragmentFunction = fragmentFunction;
        // pipelineDescriptor.supportIndirectCommandBuffers = YES;
        // TODO: UsedForIndirect?

        for (uint64 i = 0; i < desc.ColorAttachmentFormats.size(); i++) {
            pipelineDescriptor.colorAttachments[i].pixelFormat = ConvertTextureFormatToMetal(desc.ColorAttachmentFormats[i]);
            if (desc.EnableBlending) {
                pipelineDescriptor.colorAttachments[i].blendingEnabled = YES;
                pipelineDescriptor.colorAttachments[i].rgbBlendOperation = MTLBlendOperationAdd;
                pipelineDescriptor.colorAttachments[i].alphaBlendOperation = MTLBlendOperationAdd;
                pipelineDescriptor.colorAttachments[i].sourceRGBBlendFactor = MTLBlendFactorSourceAlpha;
                pipelineDescriptor.colorAttachments[i].sourceAlphaBlendFactor = MTLBlendFactorSourceAlpha;
                pipelineDescriptor.colorAttachments[i].destinationRGBBlendFactor = MTLBlendFactorOneMinusSourceAlpha;
                pipelineDescriptor.colorAttachments[i].destinationAlphaBlendFactor = MTLBlendFactorOneMinusSourceAlpha;
            } else {
                pipelineDescriptor.colorAttachments[i].blendingEnabled = NO;
            }
        }

        if (desc.DepthReadEnabled || desc.DepthWriteEnabled) {
            pipelineDescriptor.depthAttachmentPixelFormat = ConvertTextureFormatToMetal(desc.DepthAttachmentFormat);

            // Configure depth stencil state
            MTLDepthStencilDescriptor* depthStencilDescriptor = [MTLDepthStencilDescriptor new];
            depthStencilDescriptor.depthCompareFunction = (desc.DepthCompareOp == PipelineCompareOp::GREATER) ? MTLCompareFunctionGreater :
            (desc.DepthCompareOp == PipelineCompareOp::EQUAL) ? MTLCompareFunctionEqual :
            (desc.DepthCompareOp == PipelineCompareOp::LESS_EQUAL) ? MTLCompareFunctionLessEqual :
            (desc.DepthCompareOp == PipelineCompareOp::LESS) ? MTLCompareFunctionLess :
            MTLCompareFunctionAlways; // Default to always
            depthStencilDescriptor.depthWriteEnabled = desc.DepthWriteEnabled;

            m_DepthStencilState = [device->GetDevice() newDepthStencilStateWithDescriptor:depthStencilDescriptor];
        }

        pipelineDescriptor.label = [NSString stringWithUTF8String:desc.Name.c_str()];

        m_PipelineState = [device->GetDevice() newRenderPipelineStateWithDescriptor:pipelineDescriptor error:&error];
        if (error) {
            TN_ERROR("Error creating pipeline!");
        }
    }

    MetalRenderPipeline::~MetalRenderPipeline()
    {
        // Nothing to do
    }

    uint64 MetalRenderPipeline::GetSize() const
    {
        return m_PipelineState.allocatedSize;
    }
} // namespace Termina
