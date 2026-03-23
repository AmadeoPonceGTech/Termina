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

    baseSpeed = 100;
}

void Diane::firstAbility(std::shared_ptr<Enemy>target)
{
    float dmgDealt = currentAttackDamage - currentAttackDamage * (target->getCurrentArmor() / 100);
    target->setCurrentHealth(target->getCurrentHealth() - dmgDealt);

    CD1 = 1;
}

void Diane::secondAbility(std::shared_ptr<Enemy>target,  std::shared_ptr<Enemy>target2)
{
    target->setIsTaunt(true);
    target2->setIsTaunt(true);

    target->setTauntCD(3);
    target2->setTauntCD(3);

    CD2 = 6;
}

void Diane::thirdAbility(std::shared_ptr<Character>target)
{
    shield += currentAttackPower;
    target->setShield(target->getShield() + currentAttackPower);

    CD3 = 4;
}

void Diane::fourthAbility(std::shared_ptr<Character>target, std::shared_ptr<Character>target2, std::shared_ptr<Character>target3)
{
    currentArmor = currentArmor * 1.3;
    target->setCurrentArmor(target->getCurrentArmor() * 1.2);
    target2->setCurrentArmor(target->getCurrentArmor() * 1.2);
    target3->setCurrentArmor(target->getCurrentArmor() * 1.2);
}

void Diane::startRun(std::shared_ptr<Character>target, std::shared_ptr<Character>target2, std::shared_ptr<Character>target3)
{
    if (level >= 40) fourthAbility(target, target2, target3);
}

void Diane::startTurn()
{
    if (CD1 == 0) { firstAbilityUp = true; } else { firstAbilityUp = false; }
    if (CD2 == 0 && level >= 10) { secondAbilityUp = true; } else { secondAbilityUp = false; }
    if (CD3 == 0 && level >= 25) { thirdAbilityUp = true; } else { thirdAbilityUp = false; }
}

void Diane::endTurn()
{
    if (CD1 > 0) { CD1--; }
    if (CD2 > 0) { CD2--; }
    if (CD3 > 0) { CD3--; }
    if (CD4 > 0) { CD4--; }

    manageStatusEffect();
}

void Diane::Start()
{
    // Called once when the scene starts playing.
}

void Diane::Update(float deltaTime)
{

}