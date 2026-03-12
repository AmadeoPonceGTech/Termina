#pragma once

#include <Termina/Renderer/RenderPass.hpp>

namespace Termina {
    class CubesPass : public RenderPass
    {
    public:
        CubesPass();
        ~CubesPass() override = default;

        void Resize(int32 width, int32 height) override;
        void Execute(RenderPassExecuteInfo& Info) override;
    private:
        RendererTexture* m_ColorTexture;
        RendererTexture* m_DepthTexture;
    };
}
