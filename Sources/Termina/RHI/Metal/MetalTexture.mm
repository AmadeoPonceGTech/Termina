#include "MetalTexture.hpp"
#include "MetalDevice.hpp"

namespace Termina {
    MetalTexture::MetalTexture(MetalDevice* device, const TextureDesc& desc)
        : m_Parent(device)
    {
        m_Desc = desc;

        MTLTextureDescriptor* descriptor = [MTLTextureDescriptor new];
        descriptor.width = desc.Width;
        descriptor.height = desc.Height;
        descriptor.depth = desc.Depth;
        descriptor.arrayLength = desc.ArrayLayers;
        descriptor.mipmapLevelCount = desc.MipLevels;
        descriptor.pixelFormat = ConvertTextureFormatToMetal(desc.Format);
        descriptor.usage = ConvertTextureUsageToMetal(desc.Usage);
        descriptor.resourceOptions = MTLResourceStorageModePrivate;
        descriptor.textureType = ConvertTextureTypeToMetal(desc);

        m_Texture = [device->GetDevice() newTextureWithDescriptor:descriptor];
        [device->GetResidencySet() addAllocation:m_Texture];
        [device->GetResidencySet() commit];
    }

    MetalTexture::~MetalTexture()
    {
        if (m_ShouldDestroy) {
            [m_Parent->GetResidencySet() removeAllocation:m_Texture];
        }
    }

    void MetalTexture::Resize(uint32 width, uint32 height)
    {
        if (m_ShouldDestroy) {
            [m_Parent->GetResidencySet() removeAllocation:m_Texture];
        }

        m_Desc.Width = width;
        m_Desc.Height = height;
        m_CurrentLayout = TextureLayout::UNDEFINED;

        MTLTextureDescriptor* descriptor = [MTLTextureDescriptor new];
        descriptor.width = m_Desc.Width;
        descriptor.height = m_Desc.Height;
        descriptor.depth = m_Desc.Depth;
        descriptor.arrayLength = m_Desc.ArrayLayers;
        descriptor.mipmapLevelCount = m_Desc.MipLevels;
        descriptor.pixelFormat = ConvertTextureFormatToMetal(m_Desc.Format);
        descriptor.usage = ConvertTextureUsageToMetal(m_Desc.Usage);
        descriptor.resourceOptions = MTLResourceStorageModePrivate;
        descriptor.textureType = ConvertTextureTypeToMetal(m_Desc);

        m_Texture = [m_Parent->GetDevice() newTextureWithDescriptor:descriptor];
        [m_Parent->GetResidencySet() addAllocation:m_Texture];
        [m_Parent->GetResidencySet() commit];

        m_ShouldDestroy = true;
    }

    void MetalTexture::SetName(const std::string& name)
    {
        m_Texture.label = [NSString stringWithUTF8String:name.c_str()];
    }
} // namespace Termina
