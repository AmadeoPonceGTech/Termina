// FXAA.hlsl

#include "Common/Bindless.hlsli"

#pragma compute CSMain

struct PushConstants {
    int InputIndex;
    int OutputIndex;
    int Width;
    int Height;
};
PUSH_CONSTANTS(PushConstants);

// Basic luma calculation
float rgb2luma(float3 rgb) {
    return sqrt(dot(rgb, float3(0.299, 0.587, 0.114)));
}

// Manual bilinear sampling using texture loads to avoid requiring a sampler binding
float3 sampleBilinear(Texture2D<float4> tex, float2 uv) {
    float2 pixel = uv * float2(PUSH.Width, PUSH.Height) - 0.5;
    int2 ipixel = floor(pixel);
    float2 f = frac(pixel);

    int2 ip00 = clamp(ipixel, int2(0, 0), int2(PUSH.Width - 1, PUSH.Height - 1));
    int2 ip10 = clamp(ipixel + int2(1, 0), int2(0, 0), int2(PUSH.Width - 1, PUSH.Height - 1));
    int2 ip01 = clamp(ipixel + int2(0, 1), int2(0, 0), int2(PUSH.Width - 1, PUSH.Height - 1));
    int2 ip11 = clamp(ipixel + int2(1, 1), int2(0, 0), int2(PUSH.Width - 1, PUSH.Height - 1));

    float3 p00 = tex[ip00].rgb;
    float3 p10 = tex[ip10].rgb;
    float3 p01 = tex[ip01].rgb;
    float3 p11 = tex[ip11].rgb;

    float3 top = lerp(p00, p10, f.x);
    float3 bottom = lerp(p01, p11, f.x);
    return lerp(top, bottom, f.y);
}

[numthreads(8, 8, 1)]
void CSMain(uint3 id : SV_DispatchThreadID)
{
    if (id.x >= (uint)PUSH.Width || id.y >= (uint)PUSH.Height) return;

    Texture2D<float4> InputTexture = ResourceDescriptorHeap[PUSH.InputIndex];
    RWTexture2D<float4> OutputTexture = ResourceDescriptorHeap[PUSH.OutputIndex];

    float2 inverseScreenSize = float2(1.0 / PUSH.Width, 1.0 / PUSH.Height);

    float3 colorCenter = InputTexture[id.xy].rgb;
    float lumaCenter = rgb2luma(colorCenter);

    float lumaDown = rgb2luma(InputTexture[uint2(id.x, max(0, (int)id.y - 1))].rgb);
    float lumaUp = rgb2luma(InputTexture[uint2(id.x, min(PUSH.Height - 1, (int)id.y + 1))].rgb);
    float lumaLeft = rgb2luma(InputTexture[uint2(max(0, (int)id.x - 1), id.y)].rgb);
    float lumaRight = rgb2luma(InputTexture[uint2(min(PUSH.Width - 1, (int)id.x + 1), id.y)].rgb);

    float lumaMin = min(lumaCenter, min(min(lumaDown, lumaUp), min(lumaLeft, lumaRight)));
    float lumaMax = max(lumaCenter, max(max(lumaDown, lumaUp), max(lumaLeft, lumaRight)));

    float lumaRange = lumaMax - lumaMin;
    if (lumaRange < max(0.0312, lumaMax * 0.125)) {
        OutputTexture[id.xy] = float4(colorCenter, 1.0);
        return;
    }

    float lumaDownLeft = rgb2luma(InputTexture[uint2(max(0, (int)id.x - 1), max(0, (int)id.y - 1))].rgb);
    float lumaUpRight = rgb2luma(InputTexture[uint2(min(PUSH.Width - 1, (int)id.x + 1), min(PUSH.Height - 1, (int)id.y + 1))].rgb);
    float lumaUpLeft = rgb2luma(InputTexture[uint2(max(0, (int)id.x - 1), min(PUSH.Height - 1, (int)id.y + 1))].rgb);
    float lumaDownRight = rgb2luma(InputTexture[uint2(min(PUSH.Width - 1, (int)id.x + 1), max(0, (int)id.y - 1))].rgb);

    float dirDownUp = lumaDownLeft + lumaLeft + lumaUpLeft - (lumaDownRight + lumaRight + lumaUpRight);
    float dirLeftRight = lumaUpLeft + lumaUp + lumaUpRight - (lumaDownLeft + lumaDown + lumaDownRight);

    float2 dir = float2(dirDownUp, dirLeftRight);
    float dirReduce = max((lumaUp + lumaDown + lumaLeft + lumaRight) * (0.25 * 0.125), 0.0078125);
    float rcpDirMin = 1.0 / (min(abs(dir.x), abs(dir.y)) + dirReduce);

    dir = min(float2(8.0, 8.0), max(float2(-8.0, -8.0), dir * rcpDirMin)) * inverseScreenSize;

    float2 uv = (float2(id.xy) + 0.5) * inverseScreenSize;
    float3 rgbA = (1.0/2.0) * (
        sampleBilinear(InputTexture, uv + dir * (1.0/3.0 - 0.5)) +
        sampleBilinear(InputTexture, uv + dir * (2.0/3.0 - 0.5))
    );
    float3 rgbB = rgbA * (1.0/2.0) + (1.0/4.0) * (
        sampleBilinear(InputTexture, uv + dir * (0.0/3.0 - 0.5)) +
        sampleBilinear(InputTexture, uv + dir * (3.0/3.0 - 0.5))
    );

    float lumaB = rgb2luma(rgbB);
    if (lumaB < lumaMin || lumaB > lumaMax) {
        OutputTexture[id.xy] = float4(rgbA, 1.0);
    } else {
        OutputTexture[id.xy] = float4(rgbB, 1.0);
    }
}
