#pragma once

#include <Termina/RHI/Buffer.hpp>

#include <Metal/Metal.h>

namespace Termina {
    class MetalDevice;

    class MetalBuffer : public RendererBuffer
    {
    public:
        MetalBuffer(MetalDevice* device, const BufferDesc& desc);
        ~MetalBuffer() override;

        void SetName(const std::string& name) override;
        void* Map() override;
        void Unmap() override;
        uint64 GetGPUAddress() const override;

        id<MTLBuffer> GetBuffer() const { return m_Buffer; }
    private:
        MetalDevice* m_Parent;
        id<MTLBuffer> m_Buffer;
    };
} // namespace Termina
