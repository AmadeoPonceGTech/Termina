#pragma once

#include <Termina/RHI/ComputePipeline.hpp>

#include <Metal/Metal.h>

namespace Termina {
    class MetalDevice;

    class MetalComputePipeline : public ComputePipeline
    {
    public:
        MetalComputePipeline(MetalDevice* device, const ShaderModule& module, const std::string& name = "Compute Pipeline");
        ~MetalComputePipeline() = default;

        uint64 GetSize() const override { return m_PipelineState.allocatedSize; }
        id<MTLComputePipelineState> GetPipelineState() { return m_PipelineState; }
    protected:
        id<MTLComputePipelineState> m_PipelineState;
    };
} // namespace Termina
