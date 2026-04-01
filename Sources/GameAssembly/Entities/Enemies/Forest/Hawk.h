#pragma once
#include "../Enemy.h"
#include <GameAssembly/Entities/Characters/Character.h>
#include <Termina/Scripting/API/ScriptingAPI.hpp>

class Character;

class Hawk : public Enemy, public TerminaScript::ScriptableComponent
{
public :
    Hawk(int floor);
    Hawk(Termina::Actor* owner) : TerminaScript::ScriptableComponent(owner) {}

    void startTurn() override;
    void endTurn() override;
    bool entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies) override;

    void Start() override;
    void Update(float deltaTime) override;

    void dropArtefacts() override;

    void firstAbility(Character& target);
    void secondAbility(Enemy& target);
    void thirdAbility(Enemy& target);

    void fourthAbility(Enemy& target1, Enemy& target2);

    float powerAbilityOne = 0.9f;
};
