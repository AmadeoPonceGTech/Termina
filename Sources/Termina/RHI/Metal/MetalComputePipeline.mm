#include "MetalComputePipeline.hpp"
#include "MetalDevice.hpp"

#include <Termina/Core/Logger.hpp>

namespace Termina {
    MetalComputePipeline::MetalComputePipeline(MetalDevice* device, const ShaderModule& module, const std::string& name)
    {
        NSError* error = nil;
        dispatch_data_t computeData = dispatch_data_create(module.Bytecode.data(),
                                                           module.Bytecode.size(),
                                                           dispatch_get_main_queue(), NULL);
        id<MTLLibrary> computeLibrary = [device->GetDevice() newLibraryWithData:computeData error:&error];

        NSString* computeName = [NSString stringWithUTF8String:module.EntryPoint.c_str()];
        id<MTLFunction> function = [computeLibrary newFunctionWithName:computeName];

        MTLComputePipelineDescriptor* descriptor = [MTLComputePipelineDescriptor new];
        descriptor.label = [NSString stringWithUTF8String:name.c_str()];
        descriptor.computeFunction = function;

        m_PipelineState = [device->GetDevice() newComputePipelineStateWithDescriptor:descriptor options:MTLPipelineOptionNone
         reflection:nil error:&error];
        if (error) {
            TN_ERROR("Failed to create compute pipeline!");
        }
    }
} // namespace Termina
