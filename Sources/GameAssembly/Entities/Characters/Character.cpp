#include "Character.h"

Character::Character()
{
    level = 1;
    maxLevel = 50;

    XPNeededForLvl2 = 100;
    finalXPNeeded = 100000;
    currentXP = 0;
    XPNeeded = XPNeededForLvl2 + (finalXPNeeded - XPNeededForLvl2) * ((level - 1) / (maxLevel - 1));
}

void Character::levelUp()
{
    maxHealth = baseHealth + (finalHP - baseHealth) * ((level - 1) / (maxLevel - 1));
    maxAttackDamage = baseAttackDamage + (finalAD - baseAttackDamage) * ((level - 1) / (maxLevel - 1));
    maxAttackPower = baseAttackPower + (finalAP - baseAttackPower) * ((level - 1) / (maxLevel - 1));
    maxArmor = baseArmor + (finalArmor - baseArmor) * ((level - 1) / (maxLevel - 1));
    maxPowerResist = basePowerResist + (finalPR - basePowerResist) * ((level - 1) / (maxLevel - 1));

    currentXP -= XPNeeded;
    XPNeeded = XPNeededForLvl2 + (finalXPNeeded - XPNeededForLvl2) * ((level - 1) / (maxLevel - 1));
}
