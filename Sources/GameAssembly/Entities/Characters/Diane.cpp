#include "Diane.h"

Diane::Diane()
{
    name = "Diane";
    entityClass = EClass::TANK;
    description = "Diane is a women";

    baseHealth = 100;
    finalHP = 1000;
    maxHealth = baseHealth + (finalHP - baseHealth) * ((level - 1) / (maxLevel - 1));
    currentHealth = baseHealth;

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

void Diane::firstAbility(Enemy &target)
{
    float dmgDealt = currentAttackDamage - currentAttackDamage * (target.getCurrentArmor() / 100);
    target.setCurrentHealth(target.getCurrentHealth() - dmgDealt);
}

void Diane::secondAbility(Enemy &target,  Enemy &target2)
{
    //taunt
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

void Diane::checkAbilities() {

}

void Diane::startTurn()
{
    if (CD1 == 0) { firstAbilityUp = true; } else { firstAbilityUp = false; }
    if (CD2 == 0 && level >= 10) { secondAbilityUp = true; } else { secondAbilityUp = false; }
    if (CD3 == 0 && level >= 25) { thirdAbilityUp = true; } else { thirdAbilityUp = false; }
    if (CD4 == 0 && level >= 40) { fourthAbilityUp = true; } else { fourthAbilityUp = false; }
}

void Diane::endTurn()
{
    if (currentXP >= XPNeeded) { levelUp(); }

    if (CD1 > 0) { CD1--; }
    if (CD2 > 0) { CD2--; }
    if (CD3 > 0) { CD3--; }
    if (CD4 > 0) { CD4--; }
}

void Diane::Start()
{
    // Called once when the scene starts playing.
}

void Diane::Update(float deltaTime)
{

}