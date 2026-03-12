#pragma once

#include <Termina/Core/Window.hpp>
#include <Termina/RHI/Surface.hpp>

#include "MetalRenderContext.hpp"
#include "MetalTexture.hpp"
#include "MetalTextureView.hpp"

#include <GLFW/glfw3.h>
#include <QuartzCore/QuartzCore.h>
#include <dispatch/dispatch.h>

namespace Termina {
    class MetalDevice;

    class MetalSurface : public RendererSurface
    {
    public:
        MetalSurface(MetalDevice* device, Window* window);
        ~MetalSurface() override;

        RenderContext* BeginFrame() override;
        void EndFrame() override;

        RenderContext* GetContext() override { return m_RenderContext; }
        RendererTexture* GetCurrentTexture() override { return m_Texture; }
        TextureView* GetCurrentTextureView() override { return m_TextureView; }

        int GetFrameIndex() const override { return 0; }
        int GetWidth() const override { return static_cast<int>(m_Layer.drawableSize.width); }
        int GetHeight() const override { return static_cast<int>(m_Layer.drawableSize.height); }
        void Resize(int width, int height) override;

        CAMetalLayer* GetLayer() { return m_Layer; }
    private:
        MetalRenderContext* m_RenderContext;
        MetalTexture* m_Texture;
        MetalTextureView* m_TextureView;

        CAMetalLayer* m_Layer;
        Window* m_Window;
        id<CAMetalDrawable> m_CurrentDrawable;
        dispatch_semaphore_t m_FrameSemaphore;
    };
} // namespace Termina
