#pragma once
#include <vector>
#include <string>

class LogManager
{
private:
    LogManager() = default;

    std::vector<std::string> logs;
    size_t maxLogs = 100;

public:
    static LogManager& getInstance();

    void AddLog(const std::string& message);
    void DrawImGui();
};