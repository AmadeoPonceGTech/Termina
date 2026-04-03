#pragma once
#include "../Enemy.h"
#include <GameAssembly/Entities/Characters/Character.h>
#include <Termina/Scripting/API/ScriptingAPI.hpp>

class Character;

class Whale : public Enemy, public TerminaScript::ScriptableComponent
{
public :
    Whale(int floor);
    Whale(Termina::Actor* owner) : TerminaScript::ScriptableComponent(owner) {}

    void startTurn() override;
    void endTurn() override;
    bool entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies) override;

    void Start() override;
    void Update(float deltaTime) override;

    void dropArtefacts() override;

    void firstAbility(const std::vector<Character*>& targets);
    void secondAbility(const std::vector<Enemy*>& targets);
    void thirdAbility(Enemy& target);

    void fourthAbility(std::vector<std::shared_ptr<Entity>> enemies);

    std::shared_ptr<Artefact> createDrop() override;

private:
    std::shared_ptr<Enemy> selectedTarget = nullptr;
};
