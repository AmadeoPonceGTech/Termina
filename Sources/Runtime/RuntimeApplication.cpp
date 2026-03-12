#include "RuntimeApplication.hpp"
#include "ImGui/imgui.h"

#include <Termina/Renderer/Renderer.hpp>
#include <Termina/Shader/ShaderManager.hpp>

RuntimeApplication::RuntimeApplication()
    : Application("Runtime")
{
    m_SystemManager.AddSystem<Termina::RendererSystem>(m_Window);
    m_SystemManager.AddSystem<Termina::ShaderManager>();
}

void RuntimeApplication::OnUpdate(float dt)
{
    ImGui::ShowDemoWindow();
}
