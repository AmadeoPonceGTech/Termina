#pragma once

#include <Metal/Metal.h>
#include <algorithm>

#include <Termina/Core/Common.hpp>

namespace Termina {
    class MetalDevice;

    struct MetalABData
    {
        uint8 Data[128];
        uint32 DrawID;
    };

    class MetalAB
    {
    public:
        MetalAB(MetalDevice* device, uint64 maxDraws);
        ~MetalAB() = default;

        id<MTLBuffer> GetBuffer() const { return m_Buffer; }

        void Reset();
        std::pair<MetalABData*, uint64> Alloc(uint numDraws);
    private:
        id<MTLBuffer> m_Buffer;
        uint64 m_MaxDraws;
        uint64 m_Offset;
    };
}
