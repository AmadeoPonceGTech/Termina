#include "MetalSampler.hpp"
#include "MetalDevice.hpp"

namespace Termina {
    MetalSampler::MetalSampler(MetalDevice* device, SamplerDesc desc)
        : m_ParentDevice(device)
    {
        m_Desc = desc;

        MTLSamplerAddressMode addressMode;
        switch (desc.Address)
        {
            case SamplerAddressMode::WRAP:   addressMode = MTLSamplerAddressModeRepeat; break;
            case SamplerAddressMode::MIRROR: addressMode = MTLSamplerAddressModeMirrorRepeat; break;
            case SamplerAddressMode::CLAMP:  addressMode = MTLSamplerAddressModeClampToEdge; break;
            case SamplerAddressMode::BORDER: addressMode = MTLSamplerAddressModeClampToBorderColor; break;
            default:                         addressMode = MTLSamplerAddressModeRepeat; break;
        }

        MTLSamplerMinMagFilter filter;
        MTLSamplerMipFilter mipmapMode;
        switch (desc.Filter)
        {
            case SamplerFilter::LINEAR:
                filter = MTLSamplerMinMagFilterLinear;
                mipmapMode = desc.UseMips ? MTLSamplerMipFilterLinear : MTLSamplerMipFilterNotMipmapped;
                break;
            case SamplerFilter::POINT:
                filter = MTLSamplerMinMagFilterNearest;
                mipmapMode = desc.UseMips ? MTLSamplerMipFilterNearest : MTLSamplerMipFilterNotMipmapped;
                break;
            default:
                filter = MTLSamplerMinMagFilterLinear;
                mipmapMode = desc.UseMips ? MTLSamplerMipFilterLinear : MTLSamplerMipFilterNotMipmapped;
                break;
        }

        MTLCompareFunction compareFunc;
        switch (desc.ComparisonFunc)
        {
            case SamplerComparisonFunc::NEVER:          compareFunc = MTLCompareFunctionNever; break;
            case SamplerComparisonFunc::LESS:           compareFunc = MTLCompareFunctionLess; break;
            case SamplerComparisonFunc::EQUAL:          compareFunc = MTLCompareFunctionEqual; break;
            case SamplerComparisonFunc::LESS_EQUAL:     compareFunc = MTLCompareFunctionLessEqual; break;
            case SamplerComparisonFunc::GREATER:        compareFunc = MTLCompareFunctionGreater; break;
            case SamplerComparisonFunc::NOT_EQUAL:      compareFunc = MTLCompareFunctionNotEqual; break;
            case SamplerComparisonFunc::GREATER_EQUAL:  compareFunc = MTLCompareFunctionGreaterEqual; break;
            case SamplerComparisonFunc::ALWAYS:         compareFunc = MTLCompareFunctionAlways; break;
        }

        MTLSamplerDescriptor* samplerDescriptor = [MTLSamplerDescriptor new];
        samplerDescriptor.rAddressMode = addressMode;
        samplerDescriptor.sAddressMode = addressMode;
        samplerDescriptor.tAddressMode = addressMode;
        samplerDescriptor.borderColor = MTLSamplerBorderColorOpaqueBlack;
        samplerDescriptor.supportArgumentBuffers = YES;
        samplerDescriptor.minFilter = filter;
        samplerDescriptor.magFilter = filter;
        samplerDescriptor.mipFilter = mipmapMode;
        samplerDescriptor.lodMinClamp = 0.0f;
        samplerDescriptor.lodMaxClamp = desc.UseMips ? 16.0f : 0.0f;
        samplerDescriptor.maxAnisotropy = 16.0f;
        samplerDescriptor.compareFunction = compareFunc;

        m_Sampler = [device->GetDevice() newSamplerStateWithDescriptor:samplerDescriptor];
        m_BindlessHandle = device->GetBindlessManager()->WriteSampler(this);
    }

    MetalSampler::~MetalSampler()
    {
        m_ParentDevice->GetBindlessManager()->FreeSampler(m_BindlessHandle);
    }
} // namespace Termina
