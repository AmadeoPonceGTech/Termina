#include "Inventory.h"

void Inventory::addItem(const std::string& name, int amount) {
    if (amount <= 0) return;
    items[name] += amount;
}

int Inventory::getItemCount(const std::string& name) const {
    auto it = items.find(name);
    if (it != items.end()) {
        return it->second;
    }
    return 0;
}

void Inventory::removeItem(const std::string& name, int amount) {
    if (amount <= 0) return;

    auto it = items.find(name);
    if (it != items.end()) {
        it->second -= amount;

        if (it->second <= 0) {
            items.erase(it);
        }
    }
}