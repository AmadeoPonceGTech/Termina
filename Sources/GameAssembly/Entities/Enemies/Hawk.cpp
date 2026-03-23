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

bool Hawk::entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies) { return true;}

void Hawk::dropArtefacts() {

}

void Hawk::firstAbility(Character& target) {
    static std::random_device rd;   // seed unique
    static std::mt19937 rng(rd());  // moteur aléatoire
    std::uniform_int_distribution<int> dist(1, 50); // 1 à 10

    if (dist(rng) == 1) { // 1 chance sur 50
        target.setCurrentAttackDamage(std::max(0.0f, target.getCurrentAttackDamage() - 10.0f));
    }
    if (dist(rng) == 2) { // 1 chance sur 50
        target.setCurrentAttackPower(std::max(0.0f, target.getCurrentAttackPower() - 10.0f));
    }
    if (dist(rng) == 3) { // 1 chance sur 50
        target.setCurrentArmor(std::max(0.0f, target.getCurrentArmor() - 10.0f));
    }
    if (dist(rng) == 4) { // 1 chance sur 50
        target.setCurrentPowerResist(std::max(0.0f, target.getCurrentPowerResist() - 10.0f));
    }
    if (dist(rng) == 5) { // 1 chance sur 50
        target.setCurrentSpeed(std::max(0.0f, target.getCurrentSpeed() - 10.0f));
    }
}

void Hawk::secondAbility(Enemy& target) {
    target.setCurrentAttackDamage(target.getCurrentAttackDamage() + target.getCurrentAttackDamage() * 0.10f);
    CD2 = 4;
}

void Hawk::thirdAbility(Enemy& target) {
    target.setCurrentHealth(target.getCurrentHealth() + target.getMaxHealth() * 0.05f);
}

void Hawk::fourthAbility(Enemy& target1, Enemy& target2) {

    CD4 = 5;
}