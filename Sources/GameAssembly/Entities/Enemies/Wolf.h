#pragma once
#include "Enemy.h"
#include <GameAssembly/Entities/Characters/Character.h>

#include <Termina/Scripting/API/ScriptingAPI.hpp>

class Character;

class Wolf : public Enemy, public TerminaScript::ScriptableComponent
{
public :
    Wolf(int floor);
    Wolf(Termina::Actor* owner) : TerminaScript::ScriptableComponent(owner) {}

    void startTurn() override;
    void endTurn() override;

    void Start() override;
    void Update(float deltaTime) override;

    void dropArtefacts() override;

    void firstAbility(Character& target);
    void secondAbility(Character& target);
    void thirdAbility(int numberOfWolf);

    void fourthAbility(Character& target, int numberOfWolf);

    private:
    float powerAbilityOne = 0.9f;
    float powerAbilityTwo = 1.1f;
};
