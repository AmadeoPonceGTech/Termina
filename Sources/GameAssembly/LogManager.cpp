#include "LogManager.h"
#include "../ThirdParty/ImGui/imgui.h"

void LogManager::AddLog(const std::string& message)
{
    logs.push_back(message);

    if (logs.size() > maxLogs)
        logs.erase(logs.begin());
}

void LogManager::DrawImGui()
{
    ImGui::Begin("Fight Log");

    for (const auto& log : logs)
    {
        ImGui::Text("%s", log.c_str());
    }

    ImGui::End();
}
