#pragma once
#include "../Enemy.h"
#include <GameAssembly/Entities/Characters/Character.h>
#include <Termina/Scripting/API/ScriptingAPI.hpp>

class Character;

class Skeleton : public Enemy, public TerminaScript::ScriptableComponent
{
public :
    Skeleton(int floor);
    Skeleton(Termina::Actor* owner) : TerminaScript::ScriptableComponent(owner) {}

    void startTurn() override;
    void endTurn() override;
    bool entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies) override;

    void Start() override;
    void Update(float deltaTime) override;

    void dropArtefacts() override;

    void firstAbility(Character& target);
    void secondAbility();
    void thirdAbility();

    void fourthAbility();

    std::shared_ptr<Artefact> createDrop() override;

private:
    std::shared_ptr<Enemy> selectedTarget = nullptr;
};
