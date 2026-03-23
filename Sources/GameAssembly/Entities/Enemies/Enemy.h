#pragma once
#include "../Entity.h"

enum class Biome {
    FOREST,
    GRAVEYARD,
    OCEAN
};

enum class EnemyState
{
    STARTTURN,
    ACTING,
    ENDTURN
};

class Enemy : public Entity
{
public:
    Enemy();

    float baseExpDrop;
    float currentExpDrop;
    float maxExpDrop;

    float finalArmor;
    float finalPR;

    int landing;

    Biome biome;

    virtual void dropArtefacts() = 0;
    EnemyState enemyState;

};
