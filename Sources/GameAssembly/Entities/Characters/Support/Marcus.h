#pragma once
#include "../Character.h"

#include <Termina/Scripting/API/ScriptingAPI.hpp>

using namespace TerminaScript;

class Marcus : public Character, public TerminaScript::ScriptableComponent
{
public :
    Marcus();
    Marcus(Termina::Actor* owner) : TerminaScript::ScriptableComponent(owner) {}

    void startTurn() override;
    void endTurn() override;

    void Start() override;
    void Update(float deltaTime) override;

    void firstAbility(std::shared_ptr<Character>target);
    void secondAbility(std::shared_ptr<Character>target, std::shared_ptr<Character>target2, std::shared_ptr<Character>target3);
    void thirdAbility(std::shared_ptr<Character>target);
    void fourthAbility(std::shared_ptr<Character>target);
};
