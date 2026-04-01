#pragma once

#include <vector>
#include <memory>
#include <random>
#include <algorithm>
#include "../../Entities/Enemies/EnemyManager.h"
#include "../../Entities/Characters/Character.h"

enum class EBiome {
    FOREST,
    OCEAN,
    GRAVEYARD
};

enum class EGameRunState
{
    StartRun,
    StartFight,
    UpdateTurn,
    EndFight,
    EndRun
};

class Gameplay {
private:
    std::shared_ptr<EnemyManager> enemyManager;
    std::vector<std::shared_ptr<Entity>> activeCharacters;

    EGameRunState runState;
    EBiome currentBiome;

public:

    Gameplay();
    void StartRun();
    void EndRun();

    void StartFight();
    void EndFight();

    void Gameloop();
    void UpdateTurn();

    bool HasSameType(const Entity& entity) const;
    void AddToTeam(const std::shared_ptr<Entity>& entity);
    void RemoveFromTeam(const std::shared_ptr<Entity>& entity);

    bool TeamIsComplete();
    bool IsInTeam(const std::shared_ptr<Entity>& entity);

};

