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

    poisonCD = 0;
    burnCD = 0;
    tauntCD = 0;
    isStun = false;
}

void Rat::Start() {}

void Rat::Update(float deltaTime) {}

void Rat::startTurn() {
    firstAbilityUp = true;
    if (CD2 == 0) { secondAbilityUp = true; } else { secondAbilityUp = false; }
    thirdAbilityUp = true;
    if (CD4 == 0 && level > 50) { fourthAbilityUp = true; } else { fourthAbilityUp = false; }
}

void Rat::endTurn() {
    if (CD2 > 0) { CD2--; }
    if (CD4 > 0) { CD4--; }

    manageStatusEffect();
}

void Rat::dropArtefacts() {

}

void Rat::firstAbility(Character& target) {
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

    float dmgDealt = currentAttackDamage * (1.0f - target.getCurrentArmor() / 100.0f);
    target.setCurrentHealth(target.getCurrentHealth() - dmgDealt);

    if (target.getIsPoisoned()) { thirdAbility(target); }
}

void Rat::secondAbility(Character& target) {
    target.setIsPoisoned(true);

    CD2 = 3;
}

void Rat::thirdAbility(Character& target) {
    float cd = target.getPoisonCD();
    float percent = 0;
    if (cd == 5) { percent = 15.0f; }
    if (cd == 4) { percent = 12.0f; }
    if (cd == 3) { percent = 8.0f; }
    if (cd == 2) { percent = 5.0f; }
    if (cd == 1) { percent = 3.0f; }
    float dmgDealt = target.getMaxHealth() * percent / 100.0f;
    target.setCurrentHealth(target.getCurrentHealth() - dmgDealt);
}

void Rat::fourthAbility(const std::vector<Character*>& targets) {
    for (Character* target : targets) {
        if (!target) continue;
        target->setIsPoisoned(true);
        float dmgDealt = currentAttackDamage * (1.0f - target->getCurrentArmor() / 100.0f);
        target->setCurrentHealth(target->getCurrentHealth() - dmgDealt);

        if (target->getIsPoisoned()) { thirdAbility(*target); }
    }

    CD4 = 5;
}