#include "Rat.h"

#include "../Characters/Character.h"


Rat::Rat(int _level) {
    std::srand(std::time({}));

    name = "Rat";
    entityClass = EClass::ASSASSIN;
    description = "The rat is a discreet animal, very close to humans.";

    level = _level;

    finalArmor = 40;
    finalPR = 30;

    baseHealth = 20;
    maxHealth = baseHealth + ((baseHealth * 100) - baseHealth) * ((level - 1) / (maxLevel - 1));
    currentHealth = maxHealth;

    baseAttackDamage = 30;
    maxAttackDamage = baseAttackDamage + ((baseAttackDamage * 100) - baseAttackDamage) * ((level - 1) / (maxLevel - 1));
    currentAttackDamage = maxAttackDamage;

    baseAttackPower = 15;
    maxAttackPower = baseAttackPower + ((baseAttackPower * 100) - baseAttackPower) * ((level - 1) / (maxLevel - 1));
    currentAttackPower = maxAttackPower;

    baseArmor = 0.3;
    maxArmor = baseArmor + (finalArmor - baseArmor) * ((level - 1) / (maxLevel - 1));
    currentArmor = maxArmor;

    basePowerResist = 0.5;
    maxPowerResist = basePowerResist + (finalPR - basePowerResist) * ((level - 1) / (maxLevel - 1));
    currentPowerResist = maxPowerResist;

    speed = 65;

    poison = Poison::NOT_POISONED;
    burn = Burn::NOT_BURNED;
}

void Rat::Start() {

}

void Rat::Update(float deltaTime) {

}

void Rat::checkAbilities() {

}

void Rat::dropArtefacts() {

}

float Rat::firstAbility(Character& target) {
    int randomChoice = rand() % 10;
    if (randomChoice == 1) {
        target.setCurrentArmor(target.getCurrentArmor() - 10);
    }

    float dmgDealt = currentAttackDamage - currentAttackDamage * (target.getCurrentArmor() / 100);
    return dmgDealt;
}

void Rat::secondAbility(Character& target) {
    target.setIsPoisoned(true);
}

float Rat::thirdAbility(Character& target) {
    float percent = target.getPoison();
    float dmgDealt = target.getMaxHealth() * percent / 100;
    return dmgDealt;
}

// std::vector<float> Rat::fourthAbility(const std::vector<Character>& targets) {
//     std::vector<float> dmgDealt;
//     for (auto target : targets) {
//         target.setIsPoisoned(true);
//
//     }
//
// }