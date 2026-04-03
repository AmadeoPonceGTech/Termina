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

    int start = logs.size() > 20 ? logs.size() - 20 : 0;

    for (int i = start; i < logs.size(); i++)
    {
        ImGui::Text("%s", logs[i].c_str());
    }

    if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
        ImGui::SetScrollHereY(1.0f);

    ImGui::End();
}