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
#include "../PlayerXP.h"

enum class EBiome {
    FOREST,
    OCEAN,
    GRAVEYARD
};

enum class EGameRunState
{
    STARTRUN,
    CHECKUPGRADE,
    STARTFIGHT,
    UPDATEFIGHT,
    ENDFIGHT,
    ENDRUN
};

class Gameplay {
private:
    std::shared_ptr<EnemyManager> enemyManager;
    std::unique_ptr<PlayerXP> playerXP;
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

    void StartRun();
    void EndRun();

    void StartFight();
    void EndFight();

    void UpdateFight();

    void drawImGui();

public:

    Gameplay();

    void Gameloop();

    bool HasSameType(const Entity& entity) const;
    void AddToTeam(const std::shared_ptr<Entity>& entity);
    void RemoveFromTeam(const std::shared_ptr<Entity>& entity);
    std::vector<std::shared_ptr<Entity>>& getActiveCharacters();

    bool TeamIsComplete();
    bool IsInTeam(const std::shared_ptr<Entity>& entity);

    void setRunState(EGameRunState newState);
    void setRunEnded(bool gameEnded);

    bool getRunEnded() const;

};

