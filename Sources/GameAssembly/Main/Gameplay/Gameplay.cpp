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


    ///////////////////////////////////////////////////
    StartRun();
}

void Gameplay::StartRun() {
    isRunning = true;
    while (isRunning)
    {
        Gameloop();
    }
    //// Start the run and start all passif
    //// Chek if Diane is active
}


void Gameplay::EndRun() {
    isRunning = false;
    ///// End the run (lose), reset and disable passif and give reward
    ///Apply XP
}


void Gameplay::StartFight() {

    isInFight = true;

    for (auto& character : activeCharacters) {
        if (character) {
            turnOrderVector.push_back(character);
        }
    }

    /// Add all Enemy in fight to the EnemyVector
    /// create predeterminated ennemy, push in vector and rearrange order via speed
    enemyManager->createEnemy<Rat>(1);
    enemyManager->createEnemy<Wolf>(1);
    enemyManager->createEnemy<Wolf>(1);

    for (auto& ennemi : enemyManager->getEnemies()) {
        if (ennemi) {
            turnOrderVector.push_back(ennemi);
        }
    }

    UpdateTurn();

    /// Check if Emilie is there
}

void Gameplay::EndFight() {
    turnOrderVector.clear();

    for (auto& character : activeCharacters)
    {
        if (character)
            turnOrderVector.push_back(character);
    }
    enemyManager->clearEnemies();
    isInFight = false;
    /// Emilie
    /// Clean du vector enemy
}

void Gameplay::UpdateTurn()
{
    while (isInFight)
    {
        for (auto& entity : turnOrderVector)
        {
            if (!entity || entity->getIsDead())
                continue;

            entity->entityTurn(activeCharacters, enemyManager->getEnemies());
        }

        bool allPlayersDead = std::all_of( activeCharacters.begin(),activeCharacters.end(),[](const std::shared_ptr<Entity>& e){return !e || e->getIsDead();});
        bool allEnemiesDead = std::all_of(enemyManager->getEnemies().begin(),enemyManager->getEnemies().end(),[](const std::shared_ptr<Entity>& e){return !e || e->getIsDead(); });

        if (allPlayersDead)
        {
            isInFight = false;
            isRunning = false;
        }

        if (allEnemiesDead)
        {
            isInFight = false;
        }

    }
}

void Gameplay::Gameloop()
{
    StartFight();
    EndFight();
}
