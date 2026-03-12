#include "MetalAB.hpp"
#include "MetalDevice.hpp"

namespace Termina {
    MetalAB::MetalAB(MetalDevice* device, uint64 maxDraws)
    {
        m_Buffer = [device->GetDevice() newBufferWithLength:sizeof(MetalABData) * maxDraws options:MTLResourceStorageModeShared];
        m_Buffer.label = @"AB Buffer";
        [device->GetResidencySet() addAllocation:m_Buffer];
        [device->GetResidencySet() commit];

        m_MaxDraws = maxDraws;
        m_Offset = 0;
    }

    void MetalAB::Reset()
    {
        m_Offset = 0;
    }

    std::pair<MetalABData*, uint64> MetalAB::Alloc(uint numDraws)
    {
        if (m_Offset + numDraws > m_MaxDraws)
            return { nullptr, 0 };

        MetalABData* ptr = (MetalABData*)((uint8*)m_Buffer.contents + m_Offset * sizeof(MetalABData));
        uint64 currentOffset = m_Offset * sizeof(MetalABData);
        m_Offset += numDraws;
        return { ptr, currentOffset };
    }
}
