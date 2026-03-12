#include "MetalSurface.hpp"
#include "MetalDevice.hpp"

#include <Foundation/Foundation.h>
#include <Cocoa/Cocoa.h>

#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3native.h>

namespace Termina {
    MetalSurface::MetalSurface(MetalDevice* device, Window* window)
        : m_Window(window)
    {
        GLFWwindow* handle = window->GetHandle();

        m_Layer = [CAMetalLayer layer];
        m_Layer.device = device->GetDevice();
        m_Layer.pixelFormat = MTLPixelFormatBGRA8Unorm;
        m_Layer.framebufferOnly = NO;
        int fbWidth, fbHeight;
        glfwGetFramebufferSize(handle, &fbWidth, &fbHeight);
        m_Layer.drawableSize = CGSizeMake(fbWidth, fbHeight);

        NSWindow *nswindow = glfwGetCocoaWindow(handle);
        nswindow.contentView.layer = m_Layer;
        nswindow.contentView.wantsLayer = YES;

        m_Texture = new MetalTexture();
        m_Texture->m_ShouldDestroy = false;

        m_TextureView = new MetalTextureView();
        m_TextureView->m_Desc.Texture = m_Texture;

        m_RenderContext = new MetalRenderContext(device, false);
        m_FrameSemaphore = dispatch_semaphore_create(1);
    }

    MetalSurface::~MetalSurface()
    {
        delete m_Texture;
        delete m_TextureView;
        delete m_RenderContext;
    }

    RenderContext* MetalSurface::BeginFrame()
    {
        // Wait until the previous frame using this slot has finished on the GPU
        dispatch_semaphore_wait(m_FrameSemaphore, DISPATCH_TIME_FOREVER);

        // Update drawable size in case window was resized or moved to different display
        int fbWidth, fbHeight;
        glfwGetFramebufferSize(m_Window->GetHandle(), &fbWidth, &fbHeight);
        CGSize expectedSize = CGSizeMake(fbWidth, fbHeight);
        m_Layer.drawableSize = expectedSize;

        // Get the drawable - retry if size doesn't match for maximize/resize operations
        m_CurrentDrawable = [m_Layer nextDrawable];

        // For maximize operations, the drawable might not immediately match the new size
        // Retry getting drawable if there's a significant size mismatch
        int retryCount = 0;
        const int maxRetries = 3;

        while (retryCount < maxRetries) {
            CGSize actualSize = CGSizeMake(m_CurrentDrawable.texture.width, m_CurrentDrawable.texture.height);

            // Check if drawable size is reasonably close to expected size
            if (fabs(actualSize.width - expectedSize.width) <= 2.0 &&
                fabs(actualSize.height - expectedSize.height) <= 2.0) {
                break; // Size is good enough
            }

            // Release current drawable and try again
            m_CurrentDrawable = nil;

            // Force layer update and get a new drawable
            [m_Layer setNeedsDisplay];
            [m_Layer displayIfNeeded];
            m_Layer.drawableSize = expectedSize;

            m_CurrentDrawable = [m_Layer nextDrawable];
            retryCount++;
        }

        m_Texture->m_Texture = m_CurrentDrawable.texture;
        // Use the actual drawable's texture dimensions
        m_Texture->m_Desc.Width = (uint32)m_CurrentDrawable.texture.width;
        m_Texture->m_Desc.Height = (uint32)m_CurrentDrawable.texture.height;
        m_Texture->m_Desc.Usage = TextureUsage::RENDER_TARGET;
        m_Texture->m_Desc.Format = TextureFormat::BGRA8_UNORM;

        m_TextureView->m_View = m_Texture->m_Texture;
        m_TextureView->m_Desc.Dimension = TextureViewDimension::TEXTURE_2D;
        m_TextureView->m_Desc.Type = TextureViewType::RENDER_TARGET;
        m_TextureView->m_Desc.Texture = m_Texture;
        m_TextureView->m_SameAsParent = true;

        m_RenderContext->Reset();
        m_RenderContext->Begin();

        return m_RenderContext;
    }

    void MetalSurface::EndFrame()
    {
        // Signal the semaphore when the GPU finishes this frame so BeginFrame can proceed
        dispatch_semaphore_t sema = m_FrameSemaphore;
        [m_RenderContext->GetCommandBuffer() addCompletedHandler:^(id<MTLCommandBuffer>) {
            dispatch_semaphore_signal(sema);
        }];

        // Use the stored drawable from BeginFrame
        [m_RenderContext->GetCommandBuffer() presentDrawable:m_CurrentDrawable];
        [m_RenderContext->GetCommandBuffer() commit];
        m_RenderContext->End();

        // Release the drawable
        m_CurrentDrawable = nil;
    }

    void MetalSurface::Resize(int width, int height)
    {
        (void)width;
        (void)height;

        // Update the Metal layer drawable size to match the new window size
        // Use pixel dimensions for high DPI displays
        int fbWidth, fbHeight;
        glfwGetFramebufferSize(m_Window->GetHandle(), &fbWidth, &fbHeight);
        m_Layer.drawableSize = CGSizeMake(fbWidth, fbHeight);
    }
} // namespace Termina
