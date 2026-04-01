#pragma once
#include "../Enemy.h"
#include <GameAssembly/Entities/Characters/Character.h>
#include <Termina/Scripting/API/ScriptingAPI.hpp>

class Character;

class RunicDear : public Enemy, public TerminaScript::ScriptableComponent
{
public :
    RunicDear(int floor);
    RunicDear(Termina::Actor* owner) : TerminaScript::ScriptableComponent(owner) {}

    void startTurn() override;
    void endTurn() override;
    bool entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies) override;

    void Start() override;
    void Update(float deltaTime) override;

    void dropArtefacts() override;

    void firstAbility(Character& target);
    void secondAbility(Character& target, Enemy& enemyTarget);
    void thirdAbility();

    void fourthAbility(const std::vector<Character*>& targets);

private:
    std::shared_ptr<Enemy> selectedTarget = nullptr;
};
