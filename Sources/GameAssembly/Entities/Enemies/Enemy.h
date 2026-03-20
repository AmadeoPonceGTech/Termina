#pragma once
#include "../Entity.h"

enum class Biome {
    FOREST,
    GRAVEYARD,
    OCEAN
};

class Enemy : public Entity
{
public:
    Enemy();

    virtual void startTurn() = 0;
    virtual void endTurn() = 0;

    float baseExpDrop;
    float currentExpDrop;
    float maxExpDrop;

    float finalArmor;
    float finalPR;

    int landing;

    Biome biome;

    virtual void dropArtefacts() = 0;
};
