#pragma once

#include <Termina/RHI/TextureView.hpp>

#include <Metal/Metal.h>

namespace Termina {
    class MetalDevice;

    class MetalTextureView : public TextureView
    {
    public:
        MetalTextureView() = default;
        MetalTextureView(MetalDevice* parent, const TextureViewDesc& desc);
        ~MetalTextureView() override;

        int32 GetBindlessIndex() override { return m_BindlessIndex; }
        id<MTLTexture> GetView() { return m_View; }
    private:
        friend class MetalSurface;

        MetalDevice* m_Parent;

        int32 m_BindlessIndex = -1;
        id<MTLTexture> m_View;
        bool m_SameAsParent = false;
    };

    inline MTLTextureType ConvertTextureViewDescToMetalType(const TextureViewDesc& desc)
    {
        switch (desc.Dimension)
        {
            case TextureViewDimension::TEXTURE_2D: return MTLTextureType2D;
            case TextureViewDimension::TEXTURE_2D_ARRAY: return MTLTextureType2DArray;
            case TextureViewDimension::TEXTURE_3D: return MTLTextureType3D;
            case TextureViewDimension::TEXTURE_CUBE: return MTLTextureTypeCube;
        }
        return MTLTextureType2D;
    }
}
