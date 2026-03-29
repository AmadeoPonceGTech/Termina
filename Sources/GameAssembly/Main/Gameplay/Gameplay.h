#pragma once

#include <vector>
#include <memory>
#include <functional>
#include <random>
#include "../../Entities/Enemies/EnemyManager.h"

#pragma region EntityInclude

#include "../../Entities/Characters/Character.h"
#include "../../Entities/Enemies/Rat.h"
#include "../../Entities/Enemies/Wolf.h"
#pragma endregion EntityInclude

class Gameplay {
private:
    std::shared_ptr<EnemyManager> enemyManager;
    std::vector<std::shared_ptr<Entity>> activeCharacters;
    std::vector<std::shared_ptr<Entity>> turnOrderVector;

    bool isRunning = false;
    bool isInFight = false;

public:

    Gameplay();
    void StartRun();
    void EndRun();

    void StartFight();
    void EndFight();

    void Gameloop();
    void UpdateTurn();

};

