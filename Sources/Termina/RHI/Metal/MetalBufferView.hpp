#pragma once

#include <Termina/RHI/BufferView.hpp>

#include <Metal/Metal.h>

namespace Termina {
    class MetalDevice;

    class MetalBufferView : public BufferView
    {
    public:
        MetalBufferView(MetalDevice* parentDevice, const BufferViewDesc& desc);
        ~MetalBufferView() override;

        int32 GetBindlessHandle() const override { return m_BindlessIndex; }
    private:
        int32 m_BindlessIndex = -1;
        MetalDevice* m_ParentDevice;
    };
} // namespace Termina
