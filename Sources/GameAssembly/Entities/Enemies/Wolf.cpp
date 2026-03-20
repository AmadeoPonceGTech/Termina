#include "Wolf.h"
#include "../Characters/Character.h"

Wolf::Wolf(int floor) {
    name = "Wolf";
    entityClass = EClass::CLOSEDDPS;
    description = "The wolf is a cunning predator, swift and relentless in the hunt.";
    biome = Biome::FOREST;

    level = floor;
    landing = floor / 5;

    finalArmor = 55.0f;
    finalPR = 35.0f;

    baseHealth = 50.0f;
    maxHealth = baseHealth * pow(1.1f, landing);
    currentHealth = maxHealth;

    baseAttackDamage = 45.0f;
    maxAttackDamage = baseAttackDamage * pow(1.1f, landing);
    currentAttackDamage = maxAttackDamage;

    baseAttackPower = 0.0f;
    maxAttackPower = baseAttackPower * pow(1.1f, landing);
    currentAttackPower = maxAttackPower;

    baseArmor = 0.5f;
    maxArmor = baseArmor * pow(1.1f, landing);
    currentArmor = maxArmor;

    basePowerResist = 0.6f;
    maxPowerResist = basePowerResist * pow(1.1f, landing);
    currentPowerResist = maxPowerResist;

    baseSpeed = 75.0f;
    currentSpeed = baseSpeed;

    baseExpDrop = 30.0f;
    maxExpDrop = 1100.0f;
    float t = std::min(landing / 100.0f, 1.0f);
    currentExpDrop = baseExpDrop + (maxExpDrop - baseExpDrop) * t;

    poison = Poison::NOT_POISONED;
    burn = Burn::NOT_BURNED;
}

void Wolf::Start() {}

void Wolf::Update(float deltaTime) {}

void Wolf::startTurn() {}

void Wolf::endTurn() {}

void Wolf::dropArtefacts() {

}

void Wolf::firstAbility(Character& target) { // powerAbilityOne=0.9f
    float dmgDealt = currentAttackDamage * (1.0f - target.getCurrentArmor() / 100.0f);
    target.setCurrentHealth(std::max(0.0f, target.getCurrentHealth() - dmgDealt * powerAbilityOne));
}

void Wolf::secondAbility(Character& target) { // powerAbilityOne=1.1f
    float dmgDealt = currentAttackDamage * (1.0f - target.getCurrentArmor() / 100.0f);
    target.setCurrentHealth(std::max(0.0f, target.getCurrentHealth() - dmgDealt * powerAbilityTwo));
}

void Wolf::thirdAbility(int numberOfWolf) { //While there is another wolf in the fight improve their speed and attack
    int allies = std::max(0, numberOfWolf - 1);

    float attackBuff = 1.0f + 0.05f * allies;
    float speedBuff  = 1.0f + 0.05f * allies;

    currentAttackDamage = baseAttackDamage * attackBuff;
    currentSpeed = baseSpeed * speedBuff;
}

void Wolf::fourthAbility(Character& target, int numberOfWolf) { // Every Wolf attack a target with claw
    int attacks = std::max(0, numberOfWolf);

    for (int i = 0; i < attacks; i++) {
        firstAbility(target);
    }
}