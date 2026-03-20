#pragma once
#include "../Entity.h"

class Character : public Entity
{
protected :
    float XPNeededForLvl2;
    float currentXP;
    float XPNeeded;

    float finalHP;
    float finalAD;
    float finalAP;
    float finalArmor;
    float finalPR;
    float finalXPNeeded;

public:
    Character();

    virtual void startTurn() = 0;
    virtual void endTurn() = 0;

    virtual void checkAbilities() = 0;
    void levelUp();
};
