#include "Diane.h"

Diane::Diane()
{
    name = "Diane";
    entityClass = EClass::TANK;
    description = "Diane is a women";

    baseHealth = 100;
    finalHP = 1000;
    maxHealth = baseHealth + (finalHP - baseHealth) * ((level - 1) / (maxLevel - 1));
    currentHealth = maxHealth;

    baseAttackDamage = 2.5f;
    finalAD = 250;
    maxAttackDamage = baseAttackDamage + (finalAD - baseAttackDamage) * ((level - 1) / (maxLevel - 1));
    currentAttackDamage = baseAttackDamage;

    baseAttackPower = 20;
    finalAP = 200;
    maxAttackPower = baseAttackPower + (finalAP - baseAttackPower) * ((level - 1) / (maxLevel - 1));
    currentAttackPower = baseAttackPower;

    baseArmor = 5;
    finalArmor = 50;
    maxArmor = baseArmor + (finalArmor - baseArmor) * ((level - 1) / (maxLevel - 1));
    currentArmor = baseArmor;

    basePowerResist = 4;
    finalPR = 30;
    maxPowerResist = basePowerResist + (finalPR - basePowerResist) * ((level - 1) / (maxLevel - 1));
    currentPowerResist = basePowerResist;

    speed = 100;
}

float Diane::firstAbility(Enemy &target)
{
    float dmgDealt = currentAttackDamage - currentAttackDamage * (target.getCurrentArmor() / 100);
    return dmgDealt;
}

void Diane::thirdAbility(Character &target)
{
    shield += currentAttackPower;
    target.setShield(target.getShield() + currentAttackPower);
}

void Diane::fourthAbility(Character &target, Character &target2, Character &target3)
{
    currentArmor = currentArmor * 1.2;
    target.setCurrentArmor(target.getCurrentArmor() * 1.2);
    target2.setCurrentArmor(target.getCurrentArmor() * 1.2);
    target3.setCurrentArmor(target.getCurrentArmor() * 1.2);
}

void Diane::Start()
{
    // Called once when the scene starts playing.
}

void Diane::Update(float deltaTime)
{
    if (currentXP >= XPNeeded) { levelUp(); }
}
