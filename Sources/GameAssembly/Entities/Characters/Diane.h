#pragma once
#include "Character.h"
#include <GameAssembly/Entities/Enemies/Enemy.h>

#include <Termina/Scripting/API/ScriptingAPI.hpp>

using namespace TerminaScript;

class Enemy;

class Diane : public Character
{
private :

public :
    Diane();
    Diane(Termina::Actor* owner) : TerminaScript::ScriptableComponent(owner) {}

    void Start() override;
    void Update(float deltaTime) override;

    void checkAbilities() override;

    float firstAbility(Enemy &target);
    void secondAbility();
    void thirdAbility(Character &target);
    void fourthAbility(Character &target, Character &target2, Character &target3);
};
