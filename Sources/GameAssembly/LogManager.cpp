#include "LogManager.h"
#include "../ThirdParty/ImGui/imgui.h"

LogManager& LogManager::getInstance()
{
    static LogManager instance;
    return instance;
}

void LogManager::AddLog(const std::string& message)
{
    logs.push_back(message);

    if (logs.size() > maxLogs)
        logs.erase(logs.begin());
}

void LogManager::DrawImGui()
{
    ImGui::Begin("Fight Log");

    ImGui::BeginChild(
        "ScrollingRegion",
        ImVec2(0, 0),
        true,
        ImGuiWindowFlags_HorizontalScrollbar
    );

    size_t start = logs.size() > 20 ? logs.size() - 20 : 0;

    for (size_t i = start; i < logs.size(); i++)
    {
        ImGui::Text("%s", logs[i].c_str());
    }

    if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
        ImGui::SetScrollHereY(1.0f);

    ImGui::EndChild();
    ImGui::End();
}