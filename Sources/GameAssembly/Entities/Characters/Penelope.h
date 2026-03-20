#include "Character.h"
#include "../Enemies/Enemy.h"

#include <Termina/Scripting/API/ScriptingAPI.hpp>

using namespace TerminaScript;

class Enemy;

class Penelope : public Character, public TerminaScript::ScriptableComponent
{
    bool fourthAbilityActive;

public :
    Penelope();
    Penelope(Termina::Actor* owner) : TerminaScript::ScriptableComponent(owner) {}

    void startTurn() override;
    void endTurn() override;

    void Start() override;
    void Update(float deltaTime) override;

    void firstAbility(Enemy &target);
    void secondAbility(Enemy &target);
    void thirdAbility(Enemy &target);
};