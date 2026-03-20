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

    void levelUp();
    bool manageXP();
    void endRun();
};
