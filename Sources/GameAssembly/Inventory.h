#pragma once

#include <string>
#include <unordered_map>
#include "Artefacts/Artefact.h"
#include "Entities/Characters/Character.h"

class Inventory {
public:
    void addItem(const std::string& name, int amount);
    int getItemCount(const std::string& name) const;
    void removeItem(const std::string& name, int amount);

    void addArtefact(std::shared_ptr<Artefact> artefact);
    std::vector<std::shared_ptr<Artefact>> getArtefactsInventory() const;
    void removeArtefactInventory(std::shared_ptr<Artefact> artefact);

    void checkArtefactsInventory();

    const std::unordered_map<std::shared_ptr<Character>, std::shared_ptr<Artefact>>& getMapCharacterToArtefact() const {
        return mapCharacterToArtefact;
    }

    void setMapCharacterToArtefact(const std::unordered_map<std::shared_ptr<Character>, std::shared_ptr<Artefact>>& newMap) {
        mapCharacterToArtefact = newMap;
    }

private:
    std::unordered_map<std::string, int> items;
    std::vector<std::shared_ptr<Artefact>> artefactsInventory;
    std::unordered_map<std::shared_ptr<Character>, std::shared_ptr<Artefact>> mapCharacterToArtefact;
};