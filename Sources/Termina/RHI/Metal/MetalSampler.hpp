#pragma once

#include <Termina/RHI/Sampler.hpp>

#include <Metal/Metal.h>

namespace Termina {
    class MetalDevice;

    class MetalSampler : public Sampler
    {
    public:
        MetalSampler(MetalDevice* device, SamplerDesc desc);
        ~MetalSampler();

        id<MTLSamplerState> GetSampler() { return m_Sampler; }
        int32 GetBindlessHandle() const override { return m_BindlessHandle; }
    private:
        MetalDevice* m_ParentDevice;

        id<MTLSamplerState> m_Sampler;
        int32 m_BindlessHandle = -1;
    };
} // namespace Termina
