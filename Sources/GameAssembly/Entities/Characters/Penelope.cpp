#include "Penelope.h"

Penelope::Penelope()
{
    name = "Penelope";
    entityClass = EClass::ASSASSIN;
    description = "Penelope is a woman";

    baseHealth = 25;
    finalHP = 300;
    maxHealth = baseHealth + (finalHP - baseHealth) * ((level - 1) / (maxLevel - 1));
    currentHealth = maxHealth;

    baseAttackDamage = 15;
    finalAD = 450;
    maxAttackDamage = baseAttackDamage + (finalAD - baseAttackDamage) * ((level - 1) / (maxLevel - 1));
    currentAttackDamage = baseAttackDamage;

    baseAttackPower = 0;
    finalAP = 0;
    maxAttackPower = 0;
    currentAttackPower = 0;

    baseArmor = 0.5f;
    finalArmor = 15;
    maxArmor = baseArmor + (finalArmor - baseArmor) * ((level - 1) / (maxLevel - 1));
    currentArmor = baseArmor;

    basePowerResist = 1;
    finalPR = 20;
    maxPowerResist = basePowerResist + (finalPR - basePowerResist) * ((level - 1) / (maxLevel - 1));
    currentPowerResist = basePowerResist;

    baseSpeed = 62.5;

    fourthAbilityActive = false;
}

void Penelope::firstAbility(Enemy &target)
{
    float dmgDealt = currentAttackDamage - currentAttackDamage * (target.getCurrentArmor() / 100);
    target.setCurrentHealth(target.getCurrentHealth() - dmgDealt);

    CD1 = 1;
}

void Penelope::secondAbility(Enemy &target)
{
    target.setIsPoisoned(true);
    target.setPoisonCD(5);

    CD2 = 3;
}

void Penelope::thirdAbility(Enemy &target)
{
    float dmgDealt = currentAttackDamage * 2 - currentAttackDamage * (target.getCurrentArmor() / 100);
    target.setCurrentHealth(target.getCurrentHealth() - dmgDealt);
    currentHealth += dmgDealt * (80 / 100);

    CD3 = 4;
}

void Penelope::startTurn()
{
    if (CD1 == 0) { firstAbilityUp = true; } else { firstAbilityUp = false; }
    if (CD2 == 0 && level >= 8) { secondAbilityUp = true; } else { secondAbilityUp = false; }
    if (CD3 == 0 && level >= 20) { thirdAbilityUp = true; } else { thirdAbilityUp = false; }
    if (level >= 45) fourthAbilityActive = true;
}

void Penelope::endTurn()
{
    if (CD1 > 0) { CD1--; }
    if (CD2 > 0) { CD2--; }
    if (CD3 > 0) { CD3--; }

    manageStatusEffect();
}

void Penelope::Start()
{
    // Called once when the scene starts playing.
}

void Penelope::Update(float deltaTime)
{

}