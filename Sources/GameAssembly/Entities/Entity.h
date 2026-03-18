#pragma once
#include <iostream>

class Entity
{
protected:
    std::string name;
    std::string eClass;
    std::string description;

    int level;

    float baseHealth; // lvl 1 value
    float currentHealth;
    float maxHealth; // calculated depending on the level

    float baseAttackDamage;
    float currentAttackDamage;
    float maxAttackDamage;

    float baseAttackPower;
    float currentAttackPower;
    float maxAttackPower;

    float baseArmor;
    float currentArmor;
    float maxArmor;

    float basePowerResist;
    float currentPowerResist;
    float maxPowerResist;

    float speed;

public:
    Entity() = default;

    virtual void firstAbility() = 0;
    virtual void secondAbility() = 0;
    virtual void thirdAbility() = 0;
    virtual void fourthAbility() = 0;
};