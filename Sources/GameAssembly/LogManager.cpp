#include "LogManager.h"
#include "../ThirdParty/ImGui/imgui.h"
#include <sstream>

LogManager& LogManager::getInstance()
{
    static LogManager instance;
    return instance;
}

void LogManager::AddLog(const std::string& message, ImVec4 color)
{
    logs.emplace_back(message, color);

    if (logs.size() > maxLogs)
        logs.erase(logs.begin());
}

void LogManager::addSeparator(ImVec4 color)
{
    logs.emplace_back("__SEPARATOR__", color);

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
        if (logs[i].message == "__SEPARATOR__")
            ImGui::Separator();
        else
            ImGui::TextColored(logs[i].color, "%s", logs[i].message.c_str());
    }

    if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
        ImGui::SetScrollHereY(1.0f);

    ImGui::EndChild();
    ImGui::End();
}