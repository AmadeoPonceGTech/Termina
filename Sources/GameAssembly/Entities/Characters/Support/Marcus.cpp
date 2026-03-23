#include "Marcus.h"

Marcus::Marcus()
{
    name = "Marcus";
    entityClass = EClass::SUPPORT;
    description = "Marcus is a man";

    baseHealth = 30;
    finalHP = 300;
    maxHealth = baseHealth + (finalHP - baseHealth) * ((level - 1) / (maxLevel - 1));
    currentHealth = baseHealth;

    baseAttackDamage = 0;
    finalAD = 0;
    maxAttackDamage = 0;
    currentAttackDamage = 0;

    baseAttackPower = 30;
    finalAP = 300;
    maxAttackPower = baseAttackPower + (finalAP - baseAttackPower) * ((level - 1) / (maxLevel - 1));
    currentAttackPower = baseAttackPower;

    baseArmor = 0.5;
    finalArmor = 15;
    maxArmor = baseArmor + (finalArmor - baseArmor) * ((level - 1) / (maxLevel - 1));
    currentArmor = baseArmor;

    basePowerResist = 0.5;
    finalPR = 15;
    maxPowerResist = basePowerResist + (finalPR - basePowerResist) * ((level - 1) / (maxLevel - 1));
    currentPowerResist = basePowerResist;

    baseSpeed = 85;
}

void Marcus::firstAbility(std::shared_ptr<Character>target)
{
    float HPHealed = currentHealth / 2;

    target->setCurrentHealth(target->getCurrentHealth() + HPHealed);
    if (target->getCurrentHealth() > target->getMaxHealth()) { target->setCurrentHealth(target->getMaxHealth()); }

    CD1 = 1;
}

void Marcus::secondAbility(std::shared_ptr<Character>target, std::shared_ptr<Character>target2, std::shared_ptr<Character>target3)
{
    float HPHealed = currentAttackPower / 4;

    currentHealth += HPHealed;
    if (currentHealth > target->getMaxHealth()) { currentHealth = target->getMaxHealth(); }
    target->setCurrentHealth(target->getCurrentHealth() + HPHealed);
    if (target->getCurrentHealth() > target->getMaxHealth()) { target->setCurrentHealth(target->getMaxHealth()); }
    target2->setCurrentHealth(target2->getCurrentHealth() + HPHealed);
    if (target2->getCurrentHealth() > target2->getMaxHealth()) { target2->setCurrentHealth(target2->getMaxHealth()); }
    target3->setCurrentHealth(target3->getCurrentHealth() + HPHealed);
    if (target3->getCurrentHealth() > target3->getMaxHealth()) { target3->setCurrentHealth(target3->getMaxHealth()); }

    CD2 = 4;
}

void Marcus::thirdAbility(std::shared_ptr<Character>target)
{
    target->setIsBurnt(false);
    target->setBurnCD(0);
    target->setIsPoisoned(false);
    target->setPoisonCD(0);
    target->setIsStun(false);
    target->setCurrentAttackPower(target->getMaxAttackPower());
    target->setCurrentAttackDamage(target->getMaxAttackDamage());
    target->setCurrentArmor(target->getMaxArmor());
    target->setCurrentPowerResist(target->getMaxPowerResist());

    CD3 = 3;
}

void Marcus::fourthAbility(std::shared_ptr<Character>target)
{
    target->setCurrentHealth(target->getMaxHealth() / 2);

    CD4 = 9;
}

void Marcus::startTurn()
{
    if (CD1 == 0) { firstAbilityUp = true; } else { firstAbilityUp = false; }
    if (CD2 == 0 && level >= 8) { secondAbilityUp = true; } else { secondAbilityUp = false; }
    if (CD3 == 0 && level >= 20) { thirdAbilityUp = true; } else { thirdAbilityUp = false; }
    if (CD4 == 0 && level >= 35) { fourthAbilityUp = true; } else { fourthAbilityUp = false; }
}

void Marcus::endTurn()
{
    if (CD1 > 0) { CD1--; }
    if (CD2 > 0) { CD2--; }
    if (CD3 > 0) { CD3--; }
    if (CD4 > 0) { CD4--; }

    manageStatusEffect();
}

void Marcus::Start()
{
    // Called once when the scene starts playing->
}

void Marcus::Update(float deltaTime)
{

}