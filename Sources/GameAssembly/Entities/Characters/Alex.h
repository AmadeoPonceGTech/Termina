#pragma once
#include "Character.h"
#include "../Enemies/Enemy.h"

#include <Termina/Scripting/API/ScriptingAPI.hpp>

using namespace TerminaScript;

class Enemy;

class Alex : public Character, public TerminaScript::ScriptableComponent
{
private :
    bool isParring;

public :
    Alex();
    Alex(Termina::Actor* owner) : TerminaScript::ScriptableComponent(owner) {}

    void startTurn() override;
    void endTurn() override;

    void Start() override;
    void Update(float deltaTime) override;

    void checkAbilities() override;

    float firstAbility(Enemy &target);
    void secondAbility();
    float thirdAbility(Enemy &target);
    void fourthAbility();

    bool getIsParring();
    void setIsParring(bool value);
};