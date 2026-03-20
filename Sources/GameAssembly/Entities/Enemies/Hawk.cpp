#include "Hawk.h"
#include "../Characters/Character.h"

Hawk::Hawk(int floor) {
    name = "Hawk";
    entityClass = EClass::SUPPORT;
    description = "The hawk is a sharp-eyed hunter, swift in the sky and deadly in its dive.";
    biome = Biome::FOREST;

    level = floor;
    landing = floor / 5;

    finalArmor = 30.0f;
    finalPR = 30.0f;

    baseHealth = 40.0f;
    maxHealth = baseHealth * pow(1.1f, landing);
    currentHealth = maxHealth;

    baseAttackDamage = 25.0f;
    maxAttackDamage = baseAttackDamage * pow(1.1f, landing);
    currentAttackDamage = maxAttackDamage;

    baseAttackPower = 10.0f;
    maxAttackPower = baseAttackPower * pow(1.1f, landing);
    currentAttackPower = maxAttackPower;

    baseArmor = 0.3f;
    maxArmor = baseArmor * pow(1.1f, landing);
    currentArmor = maxArmor;

    basePowerResist = 0.3f;
    maxPowerResist = basePowerResist * pow(1.1f, landing);
    currentPowerResist = maxPowerResist;

    baseSpeed = 75.0f;
    currentSpeed = baseSpeed;

    baseExpDrop = 20.0f;
    maxExpDrop = 900.0f;
    float t = std::min(landing / 100.0f, 1.0f);
    currentExpDrop = baseExpDrop + (maxExpDrop - baseExpDrop) * t;

    poisonCD = 0;
    burnCD = 0;
    tauntCD = 0;
    isStun = false;
}

void Hawk::Start() {}

void Hawk::Update(float deltaTime) {}

void Hawk::startTurn() {
    firstAbilityUp = true;
    if (CD2 == 0) { secondAbilityUp = true; } else { secondAbilityUp = false; }
    thirdAbilityUp = true;
    if (CD4 == 0 && level > 50) { fourthAbilityUp = true; } else { fourthAbilityUp = false; }
}

void Hawk::endTurn() {
    if (CD2 > 0) { CD2--; }
    if (CD4 > 0) { CD4--; }

    manageStatusEffect();
}

void Hawk::dropArtefacts() {

}

void Hawk::firstAbility(Character& target) {
    static std::random_device rd;
    static std::mt19937 rng(rd());
    std::uniform_int_distribution<int> chance(1, 100);
    std::uniform_int_distribution<int> dist(1, 5);

    if (chance(rng) <= 10)
    {
        int choice = dist(rng);
        float debuff = 5.0f;

        if (choice == 1) {
            target.setCurrentAttackDamage(std::max(0.0f, target.getCurrentAttackDamage() - debuff));
        }
        else if (choice == 2) {
            target.setCurrentAttackPower(std::max(0.0f, target.getCurrentAttackPower() - debuff));
        }
        else if (choice == 3) {
            target.setCurrentArmor(std::max(0.0f, target.getCurrentArmor() - debuff));
        }
        else if (choice == 4) {
            target.setCurrentPowerResist(std::max(0.0f, target.getCurrentPowerResist() - debuff));
        }
        else if (choice == 5) {
            target.setCurrentSpeed(std::max(0.0f, target.getCurrentSpeed() - debuff));
        }
    }
}

void Hawk::secondAbility(Enemy& target) {
    target.setCurrentAttackDamage(target.getCurrentAttackDamage() + target.getCurrentAttackDamage() * 0.10f);
    target.setCurrentSpeed(target.getCurrentSpeed() + target.getCurrentSpeed() * 0.10f);
    CD2 = 4;
}

void Hawk::thirdAbility(Enemy& target) {
    target.setCurrentHealth(target.getCurrentHealth() + target.getMaxHealth() * 0.05f);
}

void Hawk::fourthAbility(Enemy& target1, Enemy& target2) {
    target1.setCurrentSpeed(target1.getCurrentSpeed() + target1.getCurrentSpeed() * 0.10f);
    target2.setCurrentSpeed(target2.getCurrentSpeed() + target2.getCurrentSpeed() * 0.10f);
    CD4 = 5;
}