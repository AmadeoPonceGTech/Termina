#pragma once

#include <Termina/RHI/RenderContext.hpp>
#include <Termina/RHI/RenderEncoder.hpp>

#include <Metal/Metal.h>

namespace Termina {
    class MetalRenderContext;
    class MetalBuffer;

    class MetalRenderEncoder : public RenderEncoder
    {
    public:
        MetalRenderEncoder(MetalRenderContext* ctx, const RenderEncoderInfo& info);

        void SetViewport(float x, float y, float width, float height) override;
        void SetScissorRect(int left, int top, int right, int bottom) override;
        void SetPipeline(Pipeline* pipeline) override;
        void SetIndexBuffer(RendererBuffer* buffer) override;
        void SetConstants(uint32 size, const void* data) override;

        void Draw(uint32 vertexCount, uint32 instanceCount, uint32 firstVertex, uint32 firstInstance) override;
        void DrawIndexed(uint32 indexCount, uint32 instanceCount, uint32 firstIndex, int32 vertexOffset, uint32 firstInstance) override;

        void End() override;
    private:
        MetalRenderContext* m_ParentCtx;
        Pipeline* m_CurrentPipeline;

        id<MTLRenderCommandEncoder> m_Encoder;
        MetalBuffer* m_CurrIndexBuffer;
    };
} // namespace Termina
