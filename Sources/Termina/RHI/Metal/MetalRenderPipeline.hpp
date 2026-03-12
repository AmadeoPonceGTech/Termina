#pragma once

#include <Termina/RHI/RenderPipeline.hpp>

#include <Metal/Metal.h>

namespace Termina {
    class MetalDevice;

    class MetalRenderPipeline : public RenderPipeline
    {
    public:
        MetalRenderPipeline(MetalDevice* device, const RenderPipelineDesc& desc);
        ~MetalRenderPipeline();

        uint64 GetSize() const override;

        id<MTLRenderPipelineState> GetPipelineState() const { return m_PipelineState; }
        id<MTLDepthStencilState> GetDepthStencilState() const { return m_DepthStencilState; }
        MTLPrimitiveType GetPrimitiveType() const { return m_PrimitiveType; }
        MTLCullMode GetCullMode() const { return m_CullMode; }
        MTLWinding GetWinding() const { return m_Winding; }
        MTLTriangleFillMode GetFillMode() const { return m_FillMode; }
    private:
        id<MTLRenderPipelineState> m_PipelineState;
        id<MTLDepthStencilState> m_DepthStencilState;
        MTLPrimitiveType m_PrimitiveType;
        MTLCullMode m_CullMode;
        MTLWinding m_Winding;
        MTLTriangleFillMode m_FillMode;
    };

    inline MTLCullMode GetMetalCullMode(PipelineCullMode mode)
    {
        switch (mode)
        {
            case PipelineCullMode::NONE:
            return MTLCullModeNone;
            case PipelineCullMode::FRONT:
            return MTLCullModeFront;
            case PipelineCullMode::BACK:
            return MTLCullModeBack;
            default:
            return MTLCullModeNone;
        }
    }

    inline MTLTriangleFillMode GetMetalFillMode(PipelineFillMode mode)
    {
        switch (mode)
        {
            case PipelineFillMode::SOLID:
            return MTLTriangleFillModeFill;
            case PipelineFillMode::WIREFRAME:
            return MTLTriangleFillModeLines;
            default:
            return MTLTriangleFillModeFill;
        }
    }

    inline MTLPrimitiveTopologyClass GetMetalTopology(PipelineTopology topology)
    {
        switch (topology)
        {
            case PipelineTopology::POINTS:
            return MTLPrimitiveTopologyClassPoint;
            case PipelineTopology::LINES:
            return MTLPrimitiveTopologyClassLine;
            case PipelineTopology::TRIANGLES:
            return MTLPrimitiveTopologyClassTriangle;
            default:
            return MTLPrimitiveTopologyClassTriangle;
        }
    }

    inline MTLPrimitiveType GetMetalCmdListTopology(PipelineTopology topology)
    {
        switch (topology)
        {
            case PipelineTopology::POINTS:
            return MTLPrimitiveTypePoint;
            case PipelineTopology::LINES:
            return MTLPrimitiveTypeLine;
            case PipelineTopology::TRIANGLES:
            return MTLPrimitiveTypeTriangle;
            default:
            return MTLPrimitiveTypeTriangle;
        }
    }
} // namespace Termina
