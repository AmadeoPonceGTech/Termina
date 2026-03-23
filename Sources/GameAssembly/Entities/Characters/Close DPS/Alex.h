#pragma once
#include "../Character.h"
#include "../../Enemies/Enemy.h"

#include <Termina/Scripting/API/ScriptingAPI.hpp>

using namespace TerminaScript;

class Enemy;

class Alex : public Character, public TerminaScript::ScriptableComponent
{
private :
    bool isParring;
    std::shared_ptr<Enemy> selectedTarget = nullptr;

public :
    Alex();
    Alex(Termina::Actor* owner) : TerminaScript::ScriptableComponent(owner) {}

    void startTurn() override;
    void endTurn() override;
    void entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies) override;

    void Start() override;
    void Update(float deltaTime) override;

    void firstAbility(std::shared_ptr<Enemy>target);
    void secondAbility();
    void thirdAbility(std::shared_ptr<Enemy>target);
    void fourthAbility();

    bool getIsParring();
};