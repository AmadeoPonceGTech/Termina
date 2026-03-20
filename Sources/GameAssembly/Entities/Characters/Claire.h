#pragma once
#include "Character.h"
#include "../Enemies/Enemy.h"

#include <Termina/Scripting/API/ScriptingAPI.hpp>

using namespace TerminaScript;

class Claire : public Character, public TerminaScript::ScriptableComponent
{
public :
    Claire();
    Claire(Termina::Actor* owner) : TerminaScript::ScriptableComponent(owner) {}

    void startTurn() override;
    void endTurn() override;

    void Start() override;
    void Update(float deltaTime) override;

    void firstAbility(Enemy &target);
    void secondAbility(Character &target);
    void thirdAbility(Enemy &target);
    void fourthAbility(Character &target);
};
