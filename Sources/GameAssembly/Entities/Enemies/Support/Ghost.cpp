#include "Ghost.h"
#include "../../Characters/Character.h"

Ghost::Ghost(int floor) {
    name = "Ghost";
    entityClass = EClass::SUPPORT;
    description = "A spirit of a dead that comes to scare the mortals.";
    biome = Biome::GRAVEYARD;

    level = floor;
    landing = floor / 5;

    finalArmor = 30.0f;
    finalPR = 40.0f;

    baseHealth = 25.0f;
    maxHealth = baseHealth * pow(1.1f, landing);
    currentHealth = maxHealth;

    baseAttackDamage = 0.0f;
    maxAttackDamage = baseAttackDamage * pow(1.1f, landing);
    currentAttackDamage = maxAttackDamage;

    baseAttackPower = 20.0f;
    maxAttackPower = baseAttackPower * pow(1.1f, landing);
    currentAttackPower = maxAttackPower;

    baseArmor = 0.1f;
    maxArmor = baseArmor * pow(1.1f, landing);
    currentArmor = maxArmor;

    basePowerResist = 0.2f;
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

void Ghost::Start() {}

void Ghost::Update(float deltaTime) {}

void Ghost::startTurn() {
    firstAbilityUp = true;
    if (CD2 == 0) { secondAbilityUp = true; } else { secondAbilityUp = false; }
    if (CD4 == 0 && level > 50) { fourthAbilityUp = true; } else { fourthAbilityUp = false; }
}

void Ghost::endTurn() {
    if (CD2 > 0) { CD2--; }
    if (CD4 > 0) { CD4--; }

    manageStatusEffect();
}

bool Ghost::entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies)
{
    switch (enemyState)
    {
    case EnemyState::STARTTURN:
        startTurn();
        enemyState = EnemyState::ACTING;
        break;

    case EnemyState::ACTING:
        {
            if (characters.empty()) return false;

            static std::random_device rd;
            static std::mt19937 rng(rd());

            std::uniform_int_distribution<int> distTarget(0, characters.size() - 1);
            Character* target = dynamic_cast<Character*>(characters[distTarget(rng)].get());
            if (!target) return false;

            std::vector<int> availableChoices;

            if (firstAbilityUp)  availableChoices.push_back(1);
            if (secondAbilityUp) availableChoices.push_back(2);
            if (fourthAbilityUp) availableChoices.push_back(3);

            if (availableChoices.empty()) return false;

            std::uniform_int_distribution<int> distChoice(0, availableChoices.size() - 1);
            int choice = availableChoices[distChoice(rng)];

            switch (choice)
            {
            case 1:
                firstAbility(*target);
                break;
            case 2:
                secondAbility(*target);
                break;
            case 3:
                    fourthAbility(*target);
                    break;
            default:
                break;
            }

            enemyState = EnemyState::ENDTURN;
            break;
        }

    case EnemyState::ENDTURN:
        endTurn();
        enemyState = EnemyState::STARTTURN;
        return true;
    }

    return false;
}

void Ghost::dropArtefacts() {

}

void Ghost::firstAbility(Character& target) {
    float dmgDealt = currentAttackDamage * (1.0f - target.getCurrentArmor() / 100.0f);
    target.setCurrentHealth(std::max(0.0f, target.getCurrentHealth() - dmgDealt));
}

void Ghost::secondAbility(Character& target) {
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
            target.setCurrentSpeed(std::max(0.0f, target.getCurrentSpeed() + debuff));
        }
    }

    CD2 = 3;
}

void Ghost::fourthAbility(Character& target) {
    for (int i = 0; i < 2; ++i)
    {
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
                target.setCurrentSpeed(std::max(0.0f, target.getCurrentSpeed() + debuff));
            }
        }
    }

    CD4 = 7;
}