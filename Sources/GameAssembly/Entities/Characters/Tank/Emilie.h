#pragma once
#include "../Character.h"
#include "../../Enemies/Enemy.h"

#include <Termina/Scripting/API/ScriptingAPI.hpp>

using namespace TerminaScript;

class Enemy;

class Emilie : public Character, public TerminaScript::ScriptableComponent
{
public :
    Emilie();
    Emilie(Termina::Actor* owner) : TerminaScript::ScriptableComponent(owner) {}

    void startTurn() override;
    void endTurn() override;
    void startFight(std::shared_ptr<Enemy> target, std::shared_ptr<Enemy> &target2, std::shared_ptr<Enemy> &target3, std::shared_ptr<Enemy> &target4);
    void endFight();

    void Start() override;
    void Update(float deltaTime) override;

    void firstAbility(std::shared_ptr<Enemy>target, std::shared_ptr<Enemy>target2, std::shared_ptr<Enemy>target3, std::shared_ptr<Enemy>target4);
    void secondAbility(std::shared_ptr<Character> target);
    void thirdAbility(std::shared_ptr<Enemy>target, std::shared_ptr<Enemy>target2, std::shared_ptr<Enemy>target3, std::shared_ptr<Enemy>target4);
    bool canBeAttacked(std::shared_ptr<Enemy> target);

private :
    std::vector<std::shared_ptr<Enemy>> enemies;
};
