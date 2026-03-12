#include "MetalBufferView.hpp"
#include "MetalDevice.hpp"

namespace Termina {
    MetalBufferView::MetalBufferView(MetalDevice* parentDevice, const BufferViewDesc& desc)
        : m_ParentDevice(parentDevice)
    {
        m_Desc = desc;
        m_BindlessIndex = parentDevice->GetBindlessManager()->WriteBufferView(this);
    }

    MetalBufferView::~MetalBufferView()
    {
        m_ParentDevice->GetBindlessManager()->Free(m_BindlessIndex);
    }
} // namespace Termina
