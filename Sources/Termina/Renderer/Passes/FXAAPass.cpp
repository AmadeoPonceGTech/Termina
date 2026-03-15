#include "FXAAPass.hpp"

#include <Termina/Core/Application.hpp>
#include <Termina/Renderer/Renderer.hpp>
#include <Termina/Shader/ShaderManager.hpp>
#include <Termina/Shader/ShaderServer.hpp>
#include "ImGui/imgui.h"
#include "RHI/TextureView.hpp"

namespace Termina {

    FXAAPass::FXAAPass()
    {
        RendererDevice* device = Application::GetSystem<RendererSystem>()->GetDevice();
        uint32 width  = Application::Get().GetWindow()->GetPixelWidth();
        uint32 height = Application::Get().GetWindow()->GetPixelHeight();

        m_FXAATexture = device->CreateTexture(TextureDesc()
            .SetSize(width, height)
            .SetFormat(TextureFormat::RGBA8_UNORM)
            .SetUsage(TextureUsage::SHADER_READ | TextureUsage::SHADER_WRITE | TextureUsage::RENDER_TARGET));
        m_FXAATexture->SetName("FXAA Output");

        ShaderServer& server = Application::GetSystem<ShaderManager>()->GetShaderServer();
        server.WatchPipeline("__TERMINA__/CORE_SHADERS/FXAA.hlsl", PipelineType::Compute);
    }

    FXAAPass::~FXAAPass()
    {
        delete m_FXAATexture;
    }

    void FXAAPass::Resize(int32 width, int32 height)
    {
        if (m_FXAATexture)
            m_FXAATexture->Resize(width, height);
    }

    void FXAAPass::Inspect()
    {
        ImGui::Checkbox("Enabled", &m_Enabled);
    }

    void FXAAPass::Execute(RenderPassExecuteInfo& info)
    {
        if (!m_Enabled) return;

        ShaderServer& server = Application::GetSystem<ShaderManager>()->GetShaderServer();
        ComputePipeline* pipeline = server.GetComputePipeline("__TERMINA__/CORE_SHADERS/FXAA.hlsl");
        if (!pipeline) return;

        RendererTexture* inputTex = info.IO->GetTexture("RendererOutput");

        info.Ctx->Barrier(TextureBarrier()
            .SetTargetTexture(m_FXAATexture)
            .SetNewLayout(TextureLayout::GENERAL)
            .SetDstAccess(ResourceAccess::SHADER_WRITE)
            .SetDstStage(PipelineStage::COMPUTE_SHADER));

        TextureView* inputSRV = info.ViewCache->GetTextureView(
            TextureViewDesc::CreateDefault(inputTex, TextureViewType::SHADER_READ, TextureViewDimension::TEXTURE_2D));
        TextureView* outputUAV = info.ViewCache->GetTextureView(
            TextureViewDesc::CreateDefault(m_FXAATexture, TextureViewType::SHADER_WRITE, TextureViewDimension::TEXTURE_2D));

        struct FXAAPushConstants { int32 InputIndex; int32 OutputIndex; int32 Width; int32 Height; };
        FXAAPushConstants pc;
        pc.InputIndex  = inputSRV->GetBindlessIndex();
        pc.OutputIndex = outputUAV->GetBindlessIndex();
        pc.Width       = info.Width;
        pc.Height      = info.Height;

        ComputeEncoder* ce = info.Ctx->CreateComputeEncoder("FXAA Pass");
        ce->SetPipeline(pipeline);
        ce->SetConstants(sizeof(pc), &pc);
        ce->Dispatch(info.Width, info.Height, 1, 8, 8, 1);
        ce->End();

        // Pass the output texture down the pipeline (e.g., to ImGuiPass or final blit)
        info.IO->RegisterTexture("RendererOutput", m_FXAATexture);

        info.Ctx->Barrier(TextureBarrier()
            .SetTargetTexture(m_FXAATexture)
            .SetNewLayout(TextureLayout::READ_ONLY)
            .SetDstAccess(ResourceAccess::SHADER_READ)
            .SetDstStage(PipelineStage::PIXEL_SHADER));
    }

} // namespace Termina
