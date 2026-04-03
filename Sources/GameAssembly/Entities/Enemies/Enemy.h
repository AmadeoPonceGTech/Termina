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
protected:

    float baseExpDrop;
    float currentExpDrop;
    float maxExpDrop;

    float finalArmor;
    float finalPR;

    int landing;

    Biome biome;

    EnemyState enemyState;



public:
    Enemy();
    virtual void dropArtefacts() = 0;
    virtual std::shared_ptr<Artefact> createDrop();

    float getCurrentExpDrop() const;

};
