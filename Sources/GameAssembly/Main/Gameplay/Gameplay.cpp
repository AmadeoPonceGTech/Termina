#include "../Gameplay/Gameplay.h"

/////// Include pour Alpha Sprint 1 ///////
#include <algorithm>

#include "../../Entities/Characters/Close DPS/Alex.h"
#include "../../Entities/Characters/Tank/Diane.h"
#include "../../Entities/Characters/Support/Marcus.h"
//////////////////////////////////////////



Gameplay::Gameplay() {
    if (!enemyManager) {
        enemyManager = std::make_shared<EnemyManager>();
    }

    ////////////// Alpha Pour Sprint 1 ////////////////
    activeCharacters.push_back(std::make_shared<Alex>());
    activeCharacters.push_back(std::make_shared<Diane>());
    activeCharacters.push_back(std::make_shared<Marcus>());



    for (auto& character : activeCharacters) {
        if (character) {
            entityGameVector.push_back(character);
        }
    }

    ///////////////////////////////////////////////////

    StartRun();
}

void Gameplay::StartRun() {
    if (isInFight)
    {
        StartFight();
    }
    //// Start the run and start all passif
    //// Chek if Diane is active
}


void Gameplay::EndRun() {
    ///// End the run (lose), reset and disable passif and give reward
    ///Apply XP
}

void Gameplay::UpdateTurn()
{
    while (isRunning)
    {
        for (auto& entity : entityGameVector)
        {
            entity->entityTurn(activeCharacters, enemyManager->getEnemies());
        }
    }
}

void Gameplay::StartFight() {

    isInFight = true;

    /// Add all Enemy in fight to the EnemyVector
    /// create predeterminated ennemy, push in vector and rearrange order via speed
    enemyManager->createEnemy<Rat>(1);
    enemyManager->createEnemy<Wolf>(1);
    enemyManager->createEnemy<Wolf>(1);

    for (auto& ennemi : enemyManager->getEnemies()) {
        if (ennemi) {
            entityGameVector.push_back(ennemi);
        }
    }
    sort (entityGameVector.begin(), entityGameVector.end());
    UpdateTurn();

    /// Check if Emilie is there
}

void Gameplay::EndFight() {
    enemyManager->clearEnemies();
    isInFight = false;
    /// Emilie
    /// Clean du vector enemy
}
