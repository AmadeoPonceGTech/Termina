#pragma once

#include <string>
#include <unordered_map>

class Inventory {
public:
    void addItem(const std::string& name, int amount);
    int getItemCount(const std::string& name) const;
    void removeItem(const std::string& name, int amount);

private:
    std::unordered_map<std::string, int> items;
};