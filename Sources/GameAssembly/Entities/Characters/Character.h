#pragma once
#include "../Entity.h"
#include "../../../ThirdParty/ImGui/imgui.h"
#include "../../../ThirdParty/ImGui/imgui_internal.h"

enum class PlayerState {
    StartTurn,
    ChoosingAbility,
    ChoosingTarget,
    Acting,
    EndTurn
};

class Character : public Entity
{
protected :
    PlayerState currentState;

    float XPNeededForLvl2;
    float currentXP;
    float XPNeeded;

    float finalHP;
    float finalAD;
    float finalAP;
    float finalArmor;
    float finalPR;
    float finalXPNeeded;

    int abilitySelected;

public:
    Character();

    void levelUp();
    bool manageXP();
    void endRun();
};
