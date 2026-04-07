#pragma once

#include <vector>
#include <memory>
#include <random>

#include "../../../ThirdParty/ImGui/imgui.h"
#include "../../../ThirdParty/ImGui/ImGuizmo.h"
#include "../../../ThirdParty/ImGui/imgui_internal.h"

#include "../../Entities/Enemies/EnemyManager.h"
#include "../../Entities/Characters/Character.h"
#include "../Inventory.h"

enum class EBiome {
    FOREST,
    OCEAN,
    GRAVEYARD
};

enum class EGameRunState
{
    StartRun,
    StartFight,
    UpdateFight,
    EndFight,
    EndRun
};

class Gameplay {
private:
    std::shared_ptr<EnemyManager> enemyManager;
    std::vector<std::shared_ptr<Entity>> activeCharacters;
    std::vector<std::shared_ptr<Entity>> speedManagerVec;
    std::vector<std::shared_ptr<Entity>> aliveCharaVec;
    std::shared_ptr<Inventory> inventory;

    EGameRunState runState;
    EBiome currentBiome;


    bool spawnBoss = false;
    std::random_device rd;

    int currentLevel = 1;
    int biomeCount = 0;

    bool runEnded = false;

    int currentEntityIndex = 0;

public:

    Gameplay();

    void StartRun();
    void EndRun();

    void StartFight();
    void EndFight();

    void Gameloop();
    void UpdateFight();

    void drawImGui();

    bool HasSameType(const Entity& entity) const;
    void AddToTeam(const std::shared_ptr<Entity>& entity);
    void RemoveFromTeam(const std::shared_ptr<Entity>& entity);

    bool TeamIsComplete();
    bool IsInTeam(const std::shared_ptr<Entity>& entity);

    void setRunState(EGameRunState newState);
    void setRunEnded(bool gameEnded);

    bool getRunEnded() const;

};

