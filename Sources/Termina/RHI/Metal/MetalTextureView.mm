#include "MetalTextureView.hpp"
#include "MetalDevice.hpp"
#include "MetalTexture.hpp"

namespace Termina {


MetalTextureView::MetalTextureView(MetalDevice* device, const TextureViewDesc& desc)
    : m_Parent(device)
{
    m_Desc = desc;
    
    id<MTLTexture> srcTexture = reinterpret_cast<MetalTexture*>(desc.Texture)->GetTexture();
    TextureDesc textureDesc = desc.Texture->GetDesc();
    TextureViewDimension srcDimension = TextureViewDimension::TEXTURE_2D;
    if (textureDesc.ArrayLayers > 1) srcDimension = TextureViewDimension::TEXTURE_2D_ARRAY;
    if (textureDesc.Depth > 1) srcDimension = TextureViewDimension::TEXTURE_3D;
    if (textureDesc.IsCubeMap) srcDimension = TextureViewDimension::TEXTURE_CUBE;
    
    // Determine if first of all we can just use the OG texture as a view
    if (desc.MipStart == 0
        && desc.MipEnd == textureDesc.MipLevels
        && desc.ArrayLayerStart == 0
        && desc.ArrayLayerEnd == textureDesc.ArrayLayers
        && desc.Format == textureDesc.Format
        && desc.Dimension == srcDimension)
    {
        m_View = srcTexture;
        m_SameAsParent = true;
        
        if (desc.Type != TextureViewType::RENDER_TARGET && desc.Type != TextureViewType::DEPTH_TARGET)
            m_BindlessIndex = device->GetBindlessManager()->WriteTextureView(this);
        
        return;
    }
    
    // Otherwise, create view!
    MTLPixelFormat srcFormat = desc.Format == TextureFormat::UNDEFINED ? ConvertTextureFormatToMetal(textureDesc.Format) : ConvertTextureFormatToMetal(desc.Format);
    m_View = [srcTexture newTextureViewWithPixelFormat:srcFormat
                                           textureType:ConvertTextureViewDescToMetalType(desc)
                                                levels:NSMakeRange(desc.MipStart, desc.MipEnd == VIEW_ALL_MIP_LEVELS ? textureDesc.MipLevels : desc.MipEnd)
                                                slices:NSMakeRange(desc.ArrayLayerStart, desc.ArrayLayerEnd == VIEW_ALL_ARRAY_LAYERS ? textureDesc.ArrayLayers : desc.ArrayLayerEnd)];
    m_View.label = desc.Name.empty() ? @"TextureView" : [NSString stringWithUTF8String:desc.Name.c_str()];
    
    [device->GetResidencySet() addAllocation:m_View];
    
    if (desc.Type != TextureViewType::RENDER_TARGET && desc.Type != TextureViewType::DEPTH_TARGET)
        m_BindlessIndex = device->GetBindlessManager()->WriteTextureView(this);
}

MetalTextureView::~MetalTextureView()
{
    if (!m_SameAsParent) {
        [m_Parent->GetResidencySet() removeAllocation:m_View];
    }
    if (m_BindlessIndex != -1) m_Parent->GetBindlessManager()->Free(m_BindlessIndex);
}


} // namespace Termina
