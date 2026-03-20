#include "Alex.h"

Alex::Alex()
{
    name = "Alex";
    entityClass = EClass::CLOSEDDPS;
    description = "Alex is a man";

    baseHealth = 50;
    finalHP = 600;
    maxHealth = baseHealth + (finalHP - baseHealth) * ((level - 1) / (maxLevel - 1));
    currentHealth = maxHealth;

    baseAttackDamage = 10.f;
    finalAD = 400;
    maxAttackDamage = baseAttackDamage + (finalAD - baseAttackDamage) * ((level - 1) / (maxLevel - 1));
    currentAttackDamage = baseAttackDamage;

    baseAttackPower = 0;
    finalAP = 0;
    maxAttackPower = 0;
    currentAttackPower = 0;

    baseArmor = 3;
    finalArmor = 30;
    maxArmor = baseArmor + (finalArmor - baseArmor) * ((level - 1) / (maxLevel - 1));
    currentArmor = baseArmor;

    basePowerResist = 0.5f;
    finalPR = 10;
    maxPowerResist = basePowerResist + (finalPR - basePowerResist) * ((level - 1) / (maxLevel - 1));
    currentPowerResist = basePowerResist;

    baseSpeed = 90;

    isParring = false;
}

void Alex::firstAbility(Enemy &target)
{
    float dmgDealt = currentAttackDamage - currentAttackDamage * (target.getCurrentArmor() / 100);
    target.setCurrentHealth(target.getCurrentHealth() - dmgDealt);

    CD1 = 1;
}

void Alex::secondAbility()
{
    isParring = true;

    CD2 = 3;
}

void Alex::thirdAbility(Enemy &target)
{
    float dmgDealt = currentAttackDamage * 2 - currentAttackDamage * (target.getCurrentArmor() / 100);
    target.setCurrentHealth(target.getCurrentHealth() - dmgDealt);

    CD3 = 3;
}

void Alex::fourthAbility()
{
    float healthPercent = currentHealth / maxHealth * 100;
    if (healthPercent > 90)
    {
        currentAttackDamage = maxAttackDamage * 1;
        currentArmor = maxArmor * 1;
        currentPowerResist = maxPowerResist * 1;
        baseSpeed = 90;
    }
    else if (healthPercent > 80)
    {
        currentAttackDamage = maxAttackDamage * 1.1;
        currentArmor = maxArmor * 1.1;
        currentPowerResist = maxPowerResist * 1.1;
        baseSpeed = 88;
    }
    else if (healthPercent > 70)
    {
        currentAttackDamage = maxAttackDamage * 1.2;
        currentArmor = maxArmor * 1.2;
        currentPowerResist = maxPowerResist * 1.2;
        baseSpeed = 86;
    }
    else if (healthPercent > 60)
    {
        currentAttackDamage = maxAttackDamage * 1.3;
        currentArmor = maxArmor * 1.3;
        currentPowerResist = maxPowerResist * 1.3;
        baseSpeed = 84;
    }
    else if (healthPercent > 50)
    {
        currentAttackDamage = maxAttackDamage * 1.4;
        currentArmor = maxArmor * 1.4;
        currentPowerResist = maxPowerResist * 1.4;
        baseSpeed = 82;
    }
    else if (healthPercent > 40)
    {
        currentAttackDamage = maxAttackDamage * 1.5;
        currentArmor = maxArmor * 1.5;
        currentPowerResist = maxPowerResist * 1.5;
        baseSpeed = 80;
    }
    else if (healthPercent > 30)
    {
        currentAttackDamage = maxAttackDamage * 1.6;
        currentArmor = maxArmor * 1.6;
        currentPowerResist = maxPowerResist * 1.6;
        baseSpeed = 78;
    }
    else if (healthPercent > 20)
    {
        currentAttackDamage = maxAttackDamage * 1.7;
        currentArmor = maxArmor * 1.7;
        currentPowerResist = maxPowerResist * 1.7;
        baseSpeed = 76;
    }
    else if (healthPercent > 10)
    {
        currentAttackDamage = maxAttackDamage * 1.8;
        currentArmor = maxArmor * 1.8;
        currentPowerResist = maxPowerResist * 1.8;
        baseSpeed = 74;
    }
    else if (healthPercent > 0)
    {
        currentAttackDamage = maxAttackDamage * 2;
        currentArmor = maxArmor * 2;
        currentPowerResist = maxPowerResist * 2;
        baseSpeed = 70;
    }
}

void Alex::startTurn()
{
    if (isParring) { isParring = false; }

    if (CD1 == 0) { firstAbilityUp = true; } else { firstAbilityUp = false; }
    if (CD2 == 0 && level >= 5) { secondAbilityUp = true; } else { secondAbilityUp = false; }
    if (CD3 == 0 && level >= 15) { thirdAbilityUp = true; } else { thirdAbilityUp = false; }
    if (level >= 30) fourthAbility();
}

void Alex::endTurn()
{
    if (CD1 > 0) { CD1--; }
    if (CD2 > 0) { CD2--; }
    if (CD3 > 0) { CD3--; }

    manageStatusEffect();
}

void Alex::Start()
{
    // Called once when the scene starts playing.
}

void Alex::Update(float deltaTime)
{

}

bool Alex::getIsParring() { return isParring; }