#pragma once
#include "../Enemy.h"
#include <GameAssembly/Entities/Characters/Character.h>
#include <Termina/Scripting/API/ScriptingAPI.hpp>

class Character;

class Dunkleosteus : public Enemy, public TerminaScript::ScriptableComponent
{
public :
    Dunkleosteus(int floor);
    Dunkleosteus(Termina::Actor* owner) : TerminaScript::ScriptableComponent(owner) {}

    void startTurn() override;
    void endTurn() override;
    bool entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies) override;

    void Start() override;
    void Update(float deltaTime) override;

    void dropArtefacts() override;

    void firstAbility(Character& target);
    void secondAbility(Character& target1, Character& target2);
    void thirdAbility(Character& target);

    void fourthAbility();

private:
    std::shared_ptr<Enemy> selectedTarget = nullptr;
};
