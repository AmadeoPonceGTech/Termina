#include "../Gameplay/Gameplay.h"

#include <algorithm>

#include "../../Entities/Characters/Tank/Diane.h"
#include "../../Entities/Characters/Tank/Emilie.h"

#include "../../Entities/Enemies/Forest/Rat.h"
#include "../../Entities/Enemies/Forest/Wolf.h"
#include "../../Entities/Enemies/Forest/Bear.h"
#include "../../Entities/Enemies/Forest/Hawk.h"
#include "../../Entities/Enemies/Graveyard/Ghost.h"
#include "../../Entities/Enemies/Graveyard/AdeptOfTheChaos.h"
#include "../../Entities/Enemies/Graveyard/DarkKnight.h"
#include "../../Entities/Enemies/Graveyard/Skeleton.h"
#include "../../Entities/Enemies/Ocean/Kelpie.h"
#include "../../Entities/Enemies/Ocean/Dunkleosteus.h"
#include "../../Entities/Enemies/Ocean/Mermaid.h"
#include "../../Entities/Enemies/Ocean/Eel.h"

#include "../../Entities/Enemies/Forest/RunicDear.h"
#include "../../Entities/Enemies/Forest/RedDragon.h"
#include "../../Entities/Enemies/Graveyard/Gargoyle.h"
#include "../../Entities/Enemies/Ocean/Whale.h"

Gameplay::Gameplay() {
    if (!enemyManager) {
        enemyManager = std::make_shared<EnemyManager>();
    }
    currentBiome = EBiome::FOREST;
}

void Gameplay::startRun() {

    auto it = std::find_if(activeCharacters.begin(), activeCharacters.end(),[](const std::shared_ptr<Entity>& e){
            return std::dynamic_pointer_cast<Diane>(e) != nullptr;
        });

    if (it != activeCharacters.end()) {
        std::shared_ptr<Diane> diane = std::dynamic_pointer_cast<Diane>(*it);
        diane->startRun(activeCharacters);
    }

    for (auto chara: activeCharacters) {
        speedManagerVec.push_back(chara);
    }
    currentLevel = 1;
}

void Gameplay::startFight() {
    static std::mt19937 rng(rd());
    std::uniform_int_distribution<int> enemyIndex(1, 4);
    std::uniform_int_distribution<int> bossIndex(1, 2);
    switch (currentBiome) {
        case EBiome::FOREST :
            if (!spawnBoss)
            {
                for (int i = 0; i < 4; i++)
                {
                    int enemyToSpawn = enemyIndex(rng);
                    if (enemyToSpawn == 1) { enemyManager->createEnemy<Rat>(currentLevel); }
                    else if (enemyToSpawn == 2) { enemyManager->createEnemy<Wolf>(currentLevel); }
                    else if (enemyToSpawn == 3) { enemyManager->createEnemy<Bear>(currentLevel); }
                    else if (enemyToSpawn == 4) { enemyManager->createEnemy<Hawk>(currentLevel); }
                }
            }
            else {

                int bossToSpawn = bossIndex(rng);
                if (bossToSpawn == 1) { enemyManager->createEnemy<RunicDear>(currentLevel); }
                else { enemyManager->createEnemy<RedDragon>(currentLevel); }

                for (int i = 0; i < 2; i++)
                {
                    int enemyToSpawn = enemyIndex(rng);
                    if (enemyToSpawn == 1) { enemyManager->createEnemy<Rat>(currentLevel); }
                    else if (enemyToSpawn == 2) { enemyManager->createEnemy<Wolf>(currentLevel); }
                    else if (enemyToSpawn == 3) { enemyManager->createEnemy<Bear>(currentLevel); }
                    else if (enemyToSpawn == 4) { enemyManager->createEnemy<Hawk>(currentLevel); }
                }
            }
            break;

        case EBiome::OCEAN :
            if (!spawnBoss)
            {
                for (int i = 0; i < 4; i++)
                {
                    int enemyToSpawn = enemyIndex(rng);
                    if (enemyToSpawn == 1) { enemyManager->createEnemy<Kelpie>(currentLevel); }
                    else if (enemyToSpawn == 2) { enemyManager->createEnemy<Dunkleosteus>(currentLevel); }
                    else if (enemyToSpawn == 3) { enemyManager->createEnemy<Mermaid>(currentLevel); }
                    else if (enemyToSpawn == 4) { enemyManager->createEnemy<Eel>(currentLevel); }
                }
            }
            else {

                int bossToSpawn = bossIndex(rng);
                if (bossToSpawn == 1) { enemyManager->createEnemy<RunicDear>(currentLevel); }
                else { enemyManager->createEnemy<RedDragon>(currentLevel); }

                for (int i = 0; i < 2; i++)
                {
                    int enemyToSpawn = enemyIndex(rng);
                    if (enemyToSpawn == 1) { enemyManager->createEnemy<Kelpie>(currentLevel); }
                    else if (enemyToSpawn == 2) { enemyManager->createEnemy<Dunkleosteus>(currentLevel); }
                    else if (enemyToSpawn == 3) { enemyManager->createEnemy<Mermaid>(currentLevel); }
                    else if (enemyToSpawn == 4) { enemyManager->createEnemy<Eel>(currentLevel); }
                }
            }
            break;

        case EBiome::GRAVEYARD :
            if (!spawnBoss)
            {
                for (int i = 0; i < 4; i++)
                {
                    int enemyToSpawn = enemyIndex(rng);
                    if (enemyToSpawn == 1) { enemyManager->createEnemy<AdeptOfTheChaos>(currentLevel); }
                    else if (enemyToSpawn == 2) { enemyManager->createEnemy<Ghost>(currentLevel); }
                    else if (enemyToSpawn == 3) { enemyManager->createEnemy<DarkKnight>(currentLevel); }
                    else if (enemyToSpawn == 4) { enemyManager->createEnemy<Skeleton>(currentLevel); }
                }
            }
            else {

                int bossToSpawn = bossIndex(rng);
                if (bossToSpawn == 1) { enemyManager->createEnemy<RunicDear>(currentLevel); }
                else { enemyManager->createEnemy<RedDragon>(currentLevel); }

                for (int i = 0; i < 2; i++)
                {
                    int enemyToSpawn = enemyIndex(rng);
                    if (enemyToSpawn == 1) { enemyManager->createEnemy<AdeptOfTheChaos>(currentLevel); }
                    else if (enemyToSpawn == 2) { enemyManager->createEnemy<Ghost>(currentLevel); }
                    else if (enemyToSpawn == 3) { enemyManager->createEnemy<DarkKnight>(currentLevel); }
                    else if (enemyToSpawn == 4) { enemyManager->createEnemy<Skeleton>(currentLevel); }
                }
            }
            break;

        default:
            break;
    }

    for (auto enemy : enemyManager->getEnemies()) { speedManagerVec.push_back(enemy); std::cout << enemy->getName() << std::endl; }

    auto it = std::find_if(activeCharacters.begin(), activeCharacters.end(),[](const std::shared_ptr<Entity>& e){
            return std::dynamic_pointer_cast<Emilie>(e) != nullptr;
        });

    if (it != activeCharacters.end()) {
        std::shared_ptr<Emilie> emilie = std::dynamic_pointer_cast<Emilie>(*it);
        emilie->startFight(enemyManager->getEnemies());
    }
}

void Gameplay::updateFight() {
    std::sort(speedManagerVec.begin(), speedManagerVec.end(), [](const std::shared_ptr<Entity> a, const std::shared_ptr<Entity> b) { return a->getCurrentSpeed() < b->getCurrentSpeed(); });
    for (auto it = speedManagerVec.begin(); it != speedManagerVec.end(); ) {
        auto entity = *it;
        //std::cout << entity->getName() << std::endl;
        if (entity->entityTurn(activeCharacters, enemyManager->getEnemies())) {
            it++;
        };
        std::erase_if(speedManagerVec, [](const std::shared_ptr<Entity>& entity) { return entity->getCurrentHealth() <= 0; });
    }
    std::erase_if(enemyManager->getEnemies(), [](const std::shared_ptr<Entity>& entity) { return entity->getCurrentHealth() <= 0; });

    if (enemyManager->getEnemies().size() == 0) {
        runState = EGameRunState::EndFight;
    }

    for (auto& chara : activeCharacters) {
        if (chara->getCurrentHealth() <= 0) {
            charaDeathCount++;
        }
    }

    if (charaDeathCount == 4) {
        runState = EGameRunState::EndRun;
    }
}

void Gameplay::endFight() {
    enemyManager->clearEnemies();

    auto it = std::find_if(activeCharacters.begin(), activeCharacters.end(),[](const std::shared_ptr<Entity>& e){
            return std::dynamic_pointer_cast<Emilie>(e) != nullptr;
        });

    if (it != activeCharacters.end()) {
        std::shared_ptr<Emilie> emilie = std::dynamic_pointer_cast<Emilie>(*it);
        emilie->endFight();
    }

    currentLevel++;

    if (currentLevel % 10 == 0) {
        spawnBoss = true;
    }

    biomeCount++;
    if (biomeCount == 10) {
        static std::mt19937 rng(rd());
        std::uniform_int_distribution<int> biomeIndex(1, 3);

        int biomeChose = biomeIndex(rng);
        if (biomeChose == 1) { currentBiome = EBiome::FOREST; }
        else if (biomeChose == 2) { currentBiome = EBiome::OCEAN; }
        else if (biomeChose == 3) { currentBiome = EBiome::GRAVEYARD; }
    }
}

void Gameplay::endRun() {
    for (auto& c : activeCharacters) {
        std::shared_ptr<Character> chara = std::dynamic_pointer_cast<Character>(c);
        chara->setArtefact(nullptr);
        chara->endRun();
    }
    runEnded = true;
}

void Gameplay::gameloop()
{
    switch (runState) {
        case EGameRunState::StartRun :
            startRun();
            std::cout << "Run started" << std::endl;
            runState = EGameRunState::StartFight;
            break;
        case EGameRunState::StartFight :
            startFight();
            std::cout << "Fight started" << std::endl;
            runState = EGameRunState::UpdateFight;
            break;
        case EGameRunState::UpdateFight :
            updateFight();
            break;
        case EGameRunState::EndFight :
            endFight();
            runState = EGameRunState::StartFight;
            break;
        case EGameRunState::EndRun :
            endRun();
            break;
    }
}

bool Gameplay::hasSameType(const Entity& entity) const
{
    return std::any_of(activeCharacters.begin(), activeCharacters.end(),
        [&entity](const std::shared_ptr<Entity>& e) {
            return typeid(*e) == typeid(entity);
        });
}

void Gameplay::addToTeam(const std::shared_ptr<Entity>& entity) {
    if (!entity) {
        std::cout << "Invalid entity\n";
        return;
    }

    if (activeCharacters.size() > 3 ) {
        std::cout << "Team Max Size Reached" << std::endl;
        return;
    }

    if (hasSameType(*entity)) {
        std::cout << entity->getName() << " is already in the team\n";
        return;
    }
    activeCharacters.push_back(entity);
    std::cout << entity->getName() << " added to team" << std::endl;
}

void Gameplay::removeFromTeam(const std::shared_ptr<Entity>& entity)
{
    if (!entity) {
        std::cout << "Invalid entity\n";
        return;
    }

    auto it = std::find(activeCharacters.begin(), activeCharacters.end(), entity);

    if (it == activeCharacters.end()) {
        std::cout << entity->getName() << " not in team\n";
        return;
    }

    activeCharacters.erase(it);
    std::cout << entity->getName() << " remove from team" << std::endl;
}


////////// Check if Team is Complete or If the character is already in team
bool Gameplay::teamIsComplete() {
    if (activeCharacters.size() == 4) {
        return true;
    }
    return false;
}

bool Gameplay::isInTeam(const std::shared_ptr<Entity> &entity) {
    auto it = std::find(activeCharacters.begin(), activeCharacters.end(), entity);
    if (it != activeCharacters.end()) {
        return true;
    }
    return false;
}

void Gameplay::setRunState(EGameRunState newState) { runState = newState; }
void Gameplay::setRunEnded(bool gameEnded) { runEnded = gameEnded; }

bool Gameplay::getRunEnded() const { return runEnded; }

std::vector<std::shared_ptr<Entity> > Gameplay::getActiveCharacters() { return activeCharacters;};

std::vector<std::shared_ptr<Entity> > Gameplay::getEnemyVector() {return enemyManager->getEnemies();}
