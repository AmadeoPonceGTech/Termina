#pragma once

#include <Termina/Renderer/RenderPass.hpp>

namespace Termina {

    /// Compute pass: FXAA applied to the LDR RendererOutput image.
    class FXAAPass : public RenderPass
    {
    public:
        FXAAPass();
        ~FXAAPass() override;

        void Resize(int32 width, int32 height) override;
        void Execute(RenderPassExecuteInfo& info) override;
        void Inspect() override;

    private:
        RendererTexture* m_FXAATexture = nullptr; // RGBA8_UNORM

        bool m_Enabled = true;
    };

} // namespace Termina
