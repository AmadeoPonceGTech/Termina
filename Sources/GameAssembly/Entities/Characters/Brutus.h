#pragma once
#include "Character.h"
#include "../Enemies/Enemy.h"

#include <Termina/Scripting/API/ScriptingAPI.hpp>

using namespace TerminaScript;

class Enemy;

class Brutus : public Character, public TerminaScript::ScriptableComponent
{
public :
    Brutus();
    Brutus(Termina::Actor* owner) : TerminaScript::ScriptableComponent(owner) {}

    void startTurn() override;
    void endTurn() override;

    void Start() override;
    void Update(float deltaTime) override;

    void firstAbility(Enemy &target);
    void secondAbility(Enemy &target);
    void thirdAbility(Enemy &target);
    void fourthAbility(Enemy &target);
};
