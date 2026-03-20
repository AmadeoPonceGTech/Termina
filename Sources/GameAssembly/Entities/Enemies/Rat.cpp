#include "Rat.h"
#include "../Characters/Character.h"

Rat::Rat(int floor) {
    name = "Rat";
    entityClass = EClass::ASSASSIN;
    description = "The rat is a discreet animal, very close to humans.";
    biome = Biome::FOREST;

    level = floor;
    landing = floor / 5;

    finalArmor = 40.0f;
    finalPR = 30.0f;

    baseHealth = 20.0f;
    maxHealth = baseHealth * pow(1.1f, landing);
    currentHealth = maxHealth;

    baseAttackDamage = 30.0f;
    maxAttackDamage = baseAttackDamage * pow(1.1f, landing);
    currentAttackDamage = maxAttackDamage;

    baseAttackPower = 15.0f;
    maxAttackPower = baseAttackPower * pow(1.1f, landing);
    currentAttackPower = maxAttackPower;

    baseArmor = 0.3f;
    maxArmor = baseArmor * pow(1.1f, landing);
    currentArmor = maxArmor;

    basePowerResist = 0.5f;
    maxPowerResist = basePowerResist * pow(1.1f, landing);
    currentPowerResist = maxPowerResist;

    baseSpeed = 65.0f;
    currentSpeed = baseSpeed;

    baseExpDrop = 25.0f;
    maxExpDrop = 1000.0f;
    float t = std::min(landing / 100.0f, 1.0f);
    currentExpDrop = baseExpDrop + (maxExpDrop - baseExpDrop) * t;

    poison = Poison::NOT_POISONED;
    burn = Burn::NOT_BURNED;
}

void Rat::Start() {}

void Rat::Update(float deltaTime) {}

void Rat::startTurn() {

}

void Rat::endTurn() {

}

void Rat::dropArtefacts() {

}

void Rat::firstAbility(Character& target) {
    static std::random_device rd;   // seed unique
    static std::mt19937 rng(rd());  // moteur aléatoire
    std::uniform_int_distribution<int> dist(1, 10); // 1 à 10

    if (dist(rng) == 1) { // 1 chance sur 10
        target.setCurrentArmor(std::max(0.0f, target.getCurrentArmor() - 10));
    }

    float dmgDealt = currentAttackDamage * (1.0f - target.getCurrentArmor() / 100.0f);
    target.setCurrentHealth(target.getCurrentHealth() - dmgDealt);
}

void Rat::secondAbility(Character& target) {
    target.setIsPoisoned(true);
}

void Rat::thirdAbility(Character& target) {
    float percent = target.getPoison();
    float dmgDealt = target.getMaxHealth() * percent / 100.0f;
    target.setCurrentHealth(target.getCurrentHealth() - dmgDealt);
}

void Rat::fourthAbility(const std::vector<Character*>& targets) {
    for (Character* target : targets) {
        if (!target) continue;
        target->setIsPoisoned(true);
        float dmgDealt = currentAttackDamage * (1.0f - target->getCurrentArmor() / 100.0f);
        target->setCurrentHealth(target->getCurrentHealth() - dmgDealt);
    }
}