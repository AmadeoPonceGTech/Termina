#if !defined(TRMN_MACOS)
    #include "Vulkan/VulkanDevice.hpp"
#else
    #include "Metal/MetalDevice.hpp"
#endif

namespace Termina {
    RendererDevice* RendererDevice::Create()
    {
        #if !defined(TRMN_MACOS)
            return new VulkanDevice();
        #else
            return new MetalDevice();
        #endif
    }
}
