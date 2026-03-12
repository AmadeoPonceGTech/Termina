#include "MetalRenderContext.hpp"
#include "MetalRenderEncoder.hpp"
#include "MetalCopyEncoder.hpp"
#include "MetalDevice.hpp"
#include "MetalComputeEncoder.hpp"

namespace Termina {
    MetalRenderContext::MetalRenderContext(MetalDevice* device, bool allocate)
        : m_ParentDevice(device)
    {
        if (!allocate) return;
        m_CommandBuffer = [device->GetCommandQueue() commandBuffer];

        m_AB = new MetalAB(device, 65536);
    }

    MetalRenderContext::~MetalRenderContext()
    {
        if (m_AB) delete m_AB;
    }

    void MetalRenderContext::Reset()
    {
        if (!m_AB) m_AB = new MetalAB(m_ParentDevice, 65536);
        m_AB->Reset();
        m_CommandBuffer = [m_ParentDevice->GetCommandQueue() commandBuffer];
        [m_ParentDevice->GetResidencySet() commit];
    }

    void MetalRenderContext::Begin()
    {
    }

    void MetalRenderContext::End()
    {
        // Don't nil the command buffer here — it must remain valid for
        // ExecuteRenderContext() to commit it. Reset() will allocate a fresh one.
    }

    void MetalRenderContext::Barrier(const TextureBarrier& textureBarrier)
    {
        (void)textureBarrier;
    }

    void MetalRenderContext::Barrier(const BufferBarrier& bufferBarrier)
    {
        (void)bufferBarrier;
    }

    void MetalRenderContext::Barrier(const BarrierGroup& barrierGroup)
    {
        (void)barrierGroup;
    }

    RenderEncoder* MetalRenderContext::CreateRenderEncoder(const RenderEncoderInfo& info)
    {
        return new MetalRenderEncoder(this, info);
    }

    CopyEncoder* MetalRenderContext::CreateCopyEncoder(const std::string& name)
    {
        return new MetalCopyEncoder(this, name);
    }

    ComputeEncoder* MetalRenderContext::CreateComputeEncoder(const std::string& name)
    {
        return new MetalComputeEncoder(this, name);
    }

    void MetalRenderContext::PushMarker(const std::string& name)
    {
        (void)name;
        // TODO: Pass to current encoder?
    }

    void MetalRenderContext::PopMarker()
    {
    }
} // namespace Termina
