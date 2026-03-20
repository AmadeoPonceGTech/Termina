#include "Edward.h"

Edward::Edward()
{
    name = "Edward";
    entityClass = EClass::RANGEDDPS;
    description = "Edward is a man";

    baseHealth = 20;
    finalHP = 250;
    maxHealth = baseHealth + (finalHP - baseHealth) * ((level - 1) / (maxLevel - 1));
    currentHealth = baseHealth;

    baseAttackDamage = 0;
    finalAD = 0;
    maxAttackDamage = 0;
    currentAttackDamage = 0;

    baseAttackPower = 20;
    finalAP = 200;
    maxAttackPower = baseAttackPower + (finalAP - baseAttackPower) * ((level - 1) / (maxLevel - 1));
    currentAttackPower = baseAttackPower;

    baseArmor = 0.25;
    finalArmor = 10;
    maxArmor = baseArmor + (finalArmor - baseArmor) * ((level - 1) / (maxLevel - 1));
    currentArmor = baseArmor;

    basePowerResist = 0.25;
    finalPR = 10;
    maxPowerResist = basePowerResist + (finalPR - basePowerResist) * ((level - 1) / (maxLevel - 1));
    currentPowerResist = basePowerResist;

    baseSpeed = 75;
}

void Edward::firstAbility(Enemy &target)
{
    float dmgDealt = currentAttackPower - currentAttackPower * (target.getCurrentPowerResist() / 100);
    target.setCurrentHealth(target.getCurrentHealth() - dmgDealt);
}

void Edward::secondAbility(Enemy &target)
{
    float dmgDealt = currentAttackPower * 2 - currentAttackPower * (target.getCurrentPowerResist() / 100);
    target.setCurrentHealth(target.getCurrentHealth() - dmgDealt);
    target.setIsBurnt(true);
    target.setBurnCD(3);
}

void Edward::thirdAbility(Enemy &target)
{
    target.setIsStun(true);
}

void Edward::fourthAbility(Enemy &target)
{
    float dmgDealt = currentAttackPower * 4 - currentAttackPower * (target.getCurrentPowerResist() / 100);
    target.setCurrentHealth(target.getCurrentHealth() - dmgDealt);
    target.setIsBurnt(true);
    target.setBurnCD(3);
}

void Edward::checkAbilities() {

}

void Edward::startTurn()
{
    if (CD1 == 0) { firstAbilityUp = true; } else { firstAbilityUp = false; }
    if (CD2 == 0 && level >= 10) { secondAbilityUp = true; } else { secondAbilityUp = false; }
    if (CD3 == 0 && level >= 25) { thirdAbilityUp = true; } else { thirdAbilityUp = false; }
    if (CD4 == 0 && level >= 40) { fourthAbilityUp = true; } else { fourthAbilityUp = false; }
}

void Edward::endTurn()
{
    if (currentXP >= XPNeeded) { levelUp(); }

    if (CD1 > 0) { CD1--; }
    if (CD2 > 0) { CD2--; }
    if (CD3 > 0) { CD3--; }
    if (CD4 > 0) { CD4--; }
}

void Edward::Start()
{
    // Called once when the scene starts playing.
}

void Edward::Update(float deltaTime)
{

}