#include "Emilie.h"

#include <algorithm>
#include <memory>

Emilie::Emilie()
{
    name = "Emilie";
    entityClass = EClass::TANK;
    description = "Emilie is a women";

    baseHealth = 90;
    finalHP = 900;
    maxHealth = baseHealth + (finalHP - baseHealth) * ((level - 1) / (maxLevel - 1));
    currentHealth = baseHealth;

    baseAttackDamage = 0;
    finalAD = 0;
    maxAttackDamage = 0;
    currentAttackDamage = 0;

    baseAttackPower = 5;
    finalAP = 300;
    maxAttackPower = baseAttackPower + (finalAP - baseAttackPower) * ((level - 1) / (maxLevel - 1));
    currentAttackPower = baseAttackPower;

    baseArmor = 2;
    finalArmor = 20;
    maxArmor = baseArmor + (finalArmor - baseArmor) * ((level - 1) / (maxLevel - 1));
    currentArmor = baseArmor;

    basePowerResist = 5;
    finalPR = 50;
    maxPowerResist = basePowerResist + (finalPR - basePowerResist) * ((level - 1) / (maxLevel - 1));
    currentPowerResist = basePowerResist;

    baseSpeed = 95;
}

void Emilie::firstAbility(Enemy &target, Enemy &target2, Enemy &target3, Enemy &target4)
{
    float dmgDealt = currentAttackDamage - currentAttackDamage * (target.getCurrentArmor() / 100);
    target.setCurrentHealth(target.getCurrentHealth() - dmgDealt / 3);

    float dmgDealt2 = currentAttackDamage - currentAttackDamage * (target2.getCurrentArmor() / 100);
    target2.setCurrentHealth(target2.getCurrentHealth() - dmgDealt2 / 3);

    float dmgDealt3 = currentAttackDamage - currentAttackDamage * (target3.getCurrentArmor() / 100);
    target3.setCurrentHealth(target3.getCurrentHealth() - dmgDealt3 / 3);

    float dmgDealt4 = currentAttackDamage - currentAttackDamage * (target4.getCurrentArmor() / 100);
    target4.setCurrentHealth(target4.getCurrentHealth() - dmgDealt4 / 3);

    CD1 = 1;
}

void Emilie::secondAbility(Character &target)
{
    target.setCurrentPowerResist(target.getCurrentPowerResist() + maxPowerResist / 2);

    CD2 = 5;
}

void Emilie::thirdAbility(Enemy &target, Enemy &target2, Enemy &target3, Enemy &target4)
{
    float dmgDealt = currentAttackDamage - currentAttackDamage * (target.getCurrentArmor() / 100);
    target.setCurrentHealth(target.getCurrentHealth() - dmgDealt / 4);
    target.setIsStun(true);

    float dmgDealt2 = currentAttackDamage - currentAttackDamage * (target2.getCurrentArmor() / 100);
    target2.setCurrentHealth(target2.getCurrentHealth() - dmgDealt2 / 4);
    target.setIsStun(true);

    float dmgDealt3 = currentAttackDamage - currentAttackDamage * (target3.getCurrentArmor() / 100);
    target3.setCurrentHealth(target3.getCurrentHealth() - dmgDealt3 / 4);
    target.setIsStun(true);

    float dmgDealt4 = currentAttackDamage - currentAttackDamage * (target4.getCurrentArmor() / 100);
    target4.setCurrentHealth(target4.getCurrentHealth() - dmgDealt4 / 4);
    target.setIsStun(true);

    CD3 = 5;
}

bool Emilie::canBeAttacked(std::shared_ptr<Enemy> target)
{
    if (std::find(enemies.begin(), enemies.end(), target) != enemies.end())
    {
        enemies.erase(std::find(enemies.begin(), enemies.end(), target));
        return false;
    }
    return true;
}

void Emilie::startTurn()
{
    if (CD1 == 0) { firstAbilityUp = true; } else { firstAbilityUp = false; }
    if (CD2 == 0 && level >= 6) { secondAbilityUp = true; } else { secondAbilityUp = false; }
    if (CD3 == 0 && level >= 20) { thirdAbilityUp = true; } else { thirdAbilityUp = false; }
}

void Emilie::endTurn()
{
    if (CD1 > 0) { CD1--; }
    if (CD2 > 0) { CD2--; }
    if (CD3 > 0) { CD3--; }

    manageStatusEffect();
}

void Emilie::startFight(std::shared_ptr<Enemy> target, std::shared_ptr<Enemy> &target2, std::shared_ptr<Enemy> &target3, std::shared_ptr<Enemy> &target4) {
    enemies.push_back(target);
    enemies.push_back(target2);
    enemies.push_back(target3);
    enemies.push_back(target4);
}

void Emilie::endFight() {
    enemies.clear();
}

void Emilie::Start()
{
    // Called once when the scene starts playing.
}

void Emilie::Update(float deltaTime)
{

}