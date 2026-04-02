#pragma once
#include "../Character.h"
#include "../../Enemies/Enemy.h"

#include <Termina/Scripting/API/ScriptingAPI.hpp>

using namespace TerminaScript;

class Enemy;

class Emilie : public Character, public TerminaScript::ScriptableComponent
{
    std::shared_ptr<Enemy> selectedTargetE = nullptr;
    std::shared_ptr<Character> selectedTargetC = nullptr;

public :
    Emilie();
    Emilie(Termina::Actor* owner) : TerminaScript::ScriptableComponent(owner) {}

    void startTurn() override;
    void endTurn() override;
    bool entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies) override;
    void startFight(std::vector<std::shared_ptr<Entity>>& enemies);
    void endFight();

    void Start() override;
    void Update(float deltaTime) override;

    void firstAbility(std::vector<std::shared_ptr<Entity>> enemies);
    void secondAbility(std::shared_ptr<Character> target);
    void thirdAbility(std::vector<std::shared_ptr<Entity>> enemies);
    bool canBeAttacked(std::shared_ptr<Enemy> target);

private :
    std::vector<std::shared_ptr<Enemy>> currentEnemies;
};
