#pragma once
#include "../Character.h"
#include "../../Enemies/Enemy.h"

#include <Termina/Scripting/API/ScriptingAPI.hpp>

using namespace TerminaScript;

class Enemy;

class Edward : public Character, public TerminaScript::ScriptableComponent
{
    std::shared_ptr<Enemy> selectedTarget = nullptr;

public :
    Edward();
    Edward(Termina::Actor* owner) : TerminaScript::ScriptableComponent(owner) {}

    void startTurn() override;
    void endTurn() override;
    bool entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies) override;

    void Start() override;
    void Update(float deltaTime) override;

    void firstAbility(std::shared_ptr<Enemy>target);
    void secondAbility(std::shared_ptr<Enemy>target);
    void thirdAbility(std::shared_ptr<Enemy>target);
    void fourthAbility(std::shared_ptr<Enemy>target);
};
