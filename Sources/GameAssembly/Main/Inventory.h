#pragma once

#include <string>
#include <unordered_map>
#include "Artefacts/Artefact.h"

class Inventory {
public:
    void addItem(const std::string& name, int amount);
    int getItemCount(const std::string& name) const;
    void removeItem(const std::string& name, int amount);

    void addArtefact(std::shared_ptr<Artefact> artefact);
    std::vector<std::shared_ptr<Artefact>> getArtefactsInventory() const;
    void removeArtefactInventory(std::shared_ptr<Artefact> artefact);

    void checkArtefactsInventory();

private:
    std::unordered_map<std::string, int> items;
    std::vector<std::shared_ptr<Artefact>> artefactsInventory;
};