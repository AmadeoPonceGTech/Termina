#pragma once
#include <vector>
#include <string>

class LogManager
{
private:
    std::vector<std::string> logs;
    size_t maxLogs = 100;

public:
    void AddLog(const std::string& message);
    void DrawImGui();
};