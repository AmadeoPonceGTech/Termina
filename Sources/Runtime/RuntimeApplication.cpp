#include "RuntimeApplication.hpp"
#include "ImGui/imgui.h"

#include <Termina/Renderer/Renderer.hpp>
#include <Termina/Shader/ShaderManager.hpp>
#include <Termina/Audio/AudioSystem.hpp>
#include <Termina/World/WorldSystem.hpp>
#include <Termina/World/ComponentRegistry.hpp>

RuntimeApplication::RuntimeApplication()
    : Application("Runtime")
{
    m_SystemManager.AddSystem<Termina::WorldSystem>();
    m_SystemManager.AddSystem<Termina::RendererSystem>(m_Window);
    m_SystemManager.AddSystem<Termina::ShaderManager>();
    m_SystemManager.AddSystem<Termina::AudioSystem>();

    Termina::ComponentRegistry::Get().Report();
}

void RuntimeApplication::OnUpdate(float dt)
{
    ImGui::ShowDemoWindow();
}
