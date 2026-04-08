#pragma once

#include <vector>
#include <memory>
#include <random>
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
    UpdateFight,
    EndFight,
    EndRun
};

class Gameplay {
private:
    std::shared_ptr<EnemyManager> enemyManager;
    std::vector<std::shared_ptr<Entity>> activeCharacters;
    std::vector<std::shared_ptr<Entity>> speedManagerVec;

    EGameRunState runState;
    EBiome currentBiome;

    bool spawnBoss = false;
    std::random_device rd;

    int currentLevel = 1;
    int charaDeathCount = 0;
    int biomeCount = 0;

    bool runEnded = false;

public:

    Gameplay();
    void startRun();
    void endRun();

    void startFight();
    void endFight();

    void gameloop();
    void updateFight();

    bool hasSameType(const Entity& entity) const;
    void addToTeam(const std::shared_ptr<Entity>& entity);
    void removeFromTeam(const std::shared_ptr<Entity>& entity);

    bool teamIsComplete();
    bool isInTeam(const std::shared_ptr<Entity>& entity);

    std::vector<std::shared_ptr<Entity>> getActiveCharacters();
    std::vector<std::shared_ptr<Entity>> getEnemyVector();

    void setRunState(EGameRunState newState);
    void setRunEnded(bool gameEnded);

    bool getRunEnded() const;

};

