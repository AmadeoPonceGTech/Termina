#pragma once
#include "Character.h"
#include "../Enemies/Enemy.h"

#include <Termina/Scripting/API/ScriptingAPI.hpp>

using namespace TerminaScript;

class Enemy;

class Diane : public Character, public TerminaScript::ScriptableComponent
{
public :
    Diane();
    Diane(Termina::Actor* owner) : TerminaScript::ScriptableComponent(owner) {}

    void startRun(Character &target, Character &target2, Character &target3);
    void startTurn() override;
    void endTurn() override;

    void Start() override;
    void Update(float deltaTime) override;

    void firstAbility(Enemy &target);
    void secondAbility(Enemy &target, Enemy &target2);
    void thirdAbility(Character &target);
    void fourthAbility(Character &target, Character &target2, Character &target3);
};
