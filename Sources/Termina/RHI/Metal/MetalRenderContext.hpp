#pragma once

#include <Termina/RHI/RenderContext.hpp>

#include <Metal/Metal.h>

#include "MetalAB.hpp"

namespace Termina {
    class MetalDevice;

    class MetalRenderContext : public RenderContext
    {
    public:
        MetalRenderContext(MetalDevice* device, bool allocate = true);
        ~MetalRenderContext() override;

        void Reset() override;
        void Begin() override;
        void End() override;

        void Barrier(const TextureBarrier& textureBarrier) override;
        void Barrier(const BufferBarrier& bufferBarrier) override;
        void Barrier(const BarrierGroup& barrierGroup) override;

        RenderEncoder* CreateRenderEncoder(const RenderEncoderInfo& info) override;
        CopyEncoder* CreateCopyEncoder(const std::string& name = "Copy Pass") override;
        ComputeEncoder* CreateComputeEncoder(const std::string& name = "Compute Pass") override;

        void PushMarker(const std::string& name) override;
        void PopMarker() override;

        id<MTLCommandBuffer> GetCommandBuffer() { return m_CommandBuffer; }
        MetalAB* GetAB() { return m_AB; }
        MetalDevice* GetParentDevice() { return m_ParentDevice; }
    private:
        id<MTLCommandBuffer> m_CommandBuffer;

        MetalDevice* m_ParentDevice = nullptr;
        MetalAB* m_AB = nullptr;
    };
} // namespace Termina
