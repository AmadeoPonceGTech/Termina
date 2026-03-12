#include "ViewportPanel.hpp"
#include "ImGui/imgui.h"
#include "Termina/Core/Application.hpp"
#include "Termina/RHI/TextureView.hpp"
#include "Termina/Renderer/Renderer.hpp"
#include "Termina/Renderer/UIUtils.hpp"

void ViewportPanel::OnImGuiRender()
{
    auto renderer = Termina::Application::Get().GetSystem<Termina::RendererSystem>();
    auto colorTexture = renderer->GetPassIO()->GetTexture("RendererOutput");

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    Termina::UIUtils::BeginEditorWindow(m_Name.c_str(), &m_Open);
    ImGui::PopStyleVar(2);
    if (colorTexture) {
        auto colorView = renderer->GetResourceViewCache()->GetTextureView(
            Termina::TextureViewDesc()
                .SetFormat(Termina::TextureFormat::RGBA8_UNORM)
                .SetType(Termina::TextureViewType::SHADER_READ)
                .SetDimension(Termina::TextureViewDimension::TEXTURE_2D)
                .SetMipRange(0, 1)
                .SetArrayLayerRange(0, 1)
                .SetTexture(colorTexture)
        );
        auto contentRegion = ImGui::GetContentRegionAvail();
        ImGui::Image((ImTextureID)colorView->GetBindlessIndex(), {contentRegion.x, contentRegion.y}, {0, 1}, {1, 0});
    }
    Termina::UIUtils::EndEditorWindow();
}
