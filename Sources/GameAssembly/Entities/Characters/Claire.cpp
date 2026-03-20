#include "Claire.h"

#include <random>

Claire::Claire()
{
    name = "Claire";
    entityClass = EClass::SUPPORT;
    description = "Claire is a man";

    baseHealth = 30;
    finalHP = 400;
    maxHealth = baseHealth + (finalHP - baseHealth) * ((level - 1) / (maxLevel - 1));
    currentHealth = baseHealth;

    baseAttackDamage = 3;
    finalAD = 100;
    maxAttackDamage = baseAttackDamage + (finalAD - baseAttackDamage) * ((level - 1) / (maxLevel - 1));
    currentAttackDamage = baseAttackDamage;

    baseAttackPower = 10;
    finalAP = 20;
    maxAttackPower = baseAttackPower + (finalAP - baseAttackPower) * ((level - 1) / (maxLevel - 1));
    currentAttackPower = baseAttackPower;

    baseArmor = 0.2;
    finalArmor = 10;
    maxArmor = baseArmor + (finalArmor - baseArmor) * ((level - 1) / (maxLevel - 1));
    currentArmor = baseArmor;

    basePowerResist = 0.4;
    finalPR = 10;
    maxPowerResist = basePowerResist + (finalPR - basePowerResist) * ((level - 1) / (maxLevel - 1));
    currentPowerResist = basePowerResist;

    baseSpeed = 80;
}

void Claire::firstAbility(Enemy &target)
{
    float dmgDealt = currentAttackDamage - currentAttackDamage * (target.getCurrentArmor() / 100);
    target.setCurrentHealth(target.getCurrentHealth() - dmgDealt);

    static std::random_device rd;
    static std::mt19937 rng(rd());
    std::uniform_int_distribution<int> chance(1, 100);
    std::uniform_int_distribution<int> dist(1, 5);

    if (chance(rng) <= 15)
    {
        float choice = dist(rng);

        if (choice == 1) {
            target.setCurrentAttackDamage(target.getCurrentAttackDamage() - target.getCurrentAttackDamage() * 0.05);
        }
        else if (choice == 2) {
            target.setCurrentAttackPower(target.getCurrentAttackPower() - target.getCurrentAttackPower() * 0.05);
        }
        else if (choice == 3) {
            target.setCurrentArmor(target.getCurrentArmor() - target.getCurrentArmor() * 0.05);
        }
        else if (choice == 4) {
            target.setCurrentPowerResist(target.getCurrentPowerResist() - target.getCurrentPowerResist() * 0.05);
        }
        else if (choice == 5) {
            target.setCurrentSpeed(target.getCurrentSpeed() + currentAttackPower);
        }
    }

    CD1 = 1;
}

void Claire::secondAbility(Character &target)
{
    target.setCurrentArmor(target.getCurrentArmor() * 1.05);
    target.setCurrentPowerResist(target.getCurrentPowerResist() * 1.05);

    CD2 = 4;
}

void Claire::thirdAbility(Enemy &target)
{
    target.setCurrentSpeed(target.getCurrentSpeed() + currentAttackPower);

    CD3 = 6;
}

void Claire::fourthAbility(Character &target)
{
    target.setCurrentAttackPower(target.getCurrentAttackPower() * 1.1);
    target.setCurrentAttackDamage(target.getCurrentAttackDamage() * 1.1);
    target.setCurrentArmor(target.getCurrentArmor() * 1.1);
    target.setCurrentPowerResist(target.getCurrentPowerResist() * 1.1);
    target.setCurrentSpeed(target.getCurrentSpeed() - currentAttackPower);

    CD4 = 11;
}

void Claire::startTurn()
{
    if (CD1 == 0) { firstAbilityUp = true; } else { firstAbilityUp = false; }
    if (CD2 == 0 && level >= 8) { secondAbilityUp = true; } else { secondAbilityUp = false; }
    if (CD3 == 0 && level >= 16) { thirdAbilityUp = true; } else { thirdAbilityUp = false; }
    if (CD4 == 0 && level >= 25) { fourthAbilityUp = true; } else { fourthAbilityUp = false; }
}

void Claire::endTurn()
{
    if (CD1 > 0) { CD1--; }
    if (CD2 > 0) { CD2--; }
    if (CD3 > 0) { CD3--; }
    if (CD4 > 0) { CD4--; }

    manageStatusEffect();
}

void Claire::Start()
{
    // Called once when the scene starts playing.
}

void Claire::Update(float deltaTime)
{

}