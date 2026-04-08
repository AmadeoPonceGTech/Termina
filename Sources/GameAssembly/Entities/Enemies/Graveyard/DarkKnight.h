#pragma once
#include "../Enemy.h"
#include <GameAssembly/Entities/Characters/Character.h>
#include <Termina/Scripting/API/ScriptingAPI.hpp>

class Character;

class DarkKnight : public Enemy, public TerminaScript::ScriptableComponent
{
public :
    DarkKnight(int floor);
    DarkKnight(Termina::Actor* owner) : TerminaScript::ScriptableComponent(owner) {}

    void startTurn() override;
    void endTurn() override;
    bool entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies) override;

    void Start() override;
    void Update(float deltaTime) override;

    void dropArtefacts() override;

    void firstAbility(Character& target);
    void secondAbility(Character& target);
    void thirdAbility();

    void fourthAbility(Character& target);

    std::shared_ptr<Artefact> createDrop() override;

private:
    std::shared_ptr<Enemy> selectedTarget = nullptr;

    float powerAbilityFour = 2.0f;
};
