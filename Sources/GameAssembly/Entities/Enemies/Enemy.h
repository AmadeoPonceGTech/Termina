#pragma once
#include "../Entity.h"

class Enemy : public Entity
{
public:
    Enemy();

    float currentXP;
    float XPNeeded;

    float finalArmor;
    float finalPR;

    virtual void dropArtefacts() = 0;
    virtual void checkAbilities() = 0;
};
