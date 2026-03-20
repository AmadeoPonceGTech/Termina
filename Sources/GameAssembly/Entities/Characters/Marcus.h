#pragma once
#include "Character.h"

#include <Termina/Scripting/API/ScriptingAPI.hpp>

using namespace TerminaScript;

class Marcus : public Character, public TerminaScript::ScriptableComponent
{
public :
    Marcus();
    Marcus(Termina::Actor* owner) : TerminaScript::ScriptableComponent(owner) {}

    void startTurn() override;
    void endTurn() override;

    void Start() override;
    void Update(float deltaTime) override;

    void firstAbility(Character &target);
    void secondAbility(Character &target, Character &target2, Character &target3);
    void thirdAbility(Character &target);
    void fourthAbility(Character &target);
};
