#include "Kelpie.h"
#include "../../Characters/Character.h"

Kelpie::Kelpie(int floor) {
    name = "Kelpie";
    entityClass = EClass::SUPPORT;
    description = "The untamed horse that everyone is afraid of.";
    biome = Biome::OCEAN;

    level = floor;
    landing = floor / 5;

    finalArmor = 30.0f;
    finalPR = 55.0f;

    baseHealth = 50.0f;
    maxHealth = baseHealth * pow(1.1f, landing);
    currentHealth = maxHealth;

    baseAttackDamage = 20.0f;
    maxAttackDamage = baseAttackDamage * pow(1.1f, landing);
    currentAttackDamage = maxAttackDamage;

    baseAttackPower = 40.0f;
    maxAttackPower = baseAttackPower * pow(1.1f, landing);
    currentAttackPower = maxAttackPower;

    baseArmor = 0.5f;
    maxArmor = baseArmor * pow(1.1f, landing);
    currentArmor = maxArmor;

    basePowerResist = 0.5f;
    maxPowerResist = basePowerResist * pow(1.1f, landing);
    currentPowerResist = maxPowerResist;

    baseSpeed = 75.0f;
    currentSpeed = baseSpeed;

    baseExpDrop = 40.0f;
    maxExpDrop = 1200.0f;
    float t = std::min(landing / 100.0f, 1.0f);
    currentExpDrop = baseExpDrop + (maxExpDrop - baseExpDrop) * t;

    poisonCD = 0;
    burnCD = 0;
    tauntCD = 0;
    isStun = false;
}

void Kelpie::Start() {}

void Kelpie::Update(float deltaTime) {}

void Kelpie::startTurn() {
    firstAbilityUp = true;
    if (CD2 == 0) { secondAbilityUp = true; } else { secondAbilityUp = false; }
}

void Kelpie::endTurn() {
    if (CD2 > 0) { CD2--; }

    manageKelpieEffects();
}

bool Kelpie::entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies)
{
    switch (enemyState)
    {
    case EnemyState::STARTTURN:
        startTurn();
        enemyState = EnemyState::ACTING;
        for (auto character : characters )
        {
            if (character->getIsPoisoned())
            {
                character->setIsPoisoned(false);
                setIsPoisoned(true);
            }
        }
        break;

    case EnemyState::ACTING:
        {
            if (characters.empty()) return false;

            static std::random_device rd;
            static std::mt19937 rng(rd());

            std::uniform_int_distribution<int> distTarget(0, characters.size() - 1);
            Character* target = dynamic_cast<Character*>(characters[distTarget(rng)].get());
            Character* target2 = dynamic_cast<Character*>(characters[distTarget(rng)].get());
            Character* target3 = dynamic_cast<Character*>(characters[distTarget(rng)].get());
            if (!target) return false;

            std::vector<int> availableChoices;

            if (firstAbilityUp)  availableChoices.push_back(1);
            if (secondAbilityUp) availableChoices.push_back(2);

            if (availableChoices.empty()) return false;

            std::uniform_int_distribution<int> distChoice(0, availableChoices.size() - 1);
            int choice = availableChoices[distChoice(rng)];

            switch (choice)
            {
            case 1:
                firstAbility(*target);
                break;
            case 2:
                secondAbility(*target, *target2, *target3);
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

void Kelpie::firstAbility(Character& target) {
    float dmgDealt = currentAttackPower * (1.0f - target.getCurrentPowerResist() / 100.0f);
    target.setCurrentHealth(std::max(0.0f, target.getCurrentHealth() - dmgDealt));
}

void Kelpie::secondAbility(Character& target1, Character& target2, Character& target3) {
    float dmgDealt1 = currentAttackPower * (1.0f - target1.getCurrentPowerResist() / 100.0f);
    target1.setCurrentHealth(std::max(0.0f, target1.getCurrentHealth() - dmgDealt1));

    float dmgDealt2 = currentAttackPower * (1.0f - target2.getCurrentPowerResist() / 100.0f);
    target2.setCurrentHealth(std::max(0.0f, target2.getCurrentHealth() - dmgDealt2));

    float dmgDealt3 = currentAttackPower * (1.0f - target3.getCurrentPowerResist() / 100.0f);
    target3.setCurrentHealth(std::max(0.0f, target3.getCurrentHealth() - dmgDealt3));

    CD2 = 4;
}

void Kelpie::thirdAbility() {

}

void Kelpie::fourthAbility() {

}

void Kelpie::manageKelpieEffects()
{
    if (isPoisoned)
    {
        if (poisonCD == 5) {
            currentHealth += maxHealth * (15 / 100);
            poisonCD--;
        }
        else if (poisonCD == 4) {
            currentHealth += maxHealth * (12 / 100);
            poisonCD--;
        }
        else if (poisonCD == 3) {
            currentHealth += maxHealth * (8 / 100);
            poisonCD--;
        }
        else if (poisonCD == 2) {
            currentHealth += maxHealth * (5 / 100);
            poisonCD--;
        }
        else if (poisonCD == 1) {
            currentHealth += maxHealth * (3 / 100);
            poisonCD--;
            isPoisoned = false;
        }
    }

    if (isBurnt)
    {
        if (burnCD == 3) {
            currentHealth -= maxHealth * (15 / 100);
            burnCD--;
        }
        else if (burnCD == 2) {
            currentHealth -= maxHealth * (10 / 100);
            burnCD--;
        }
        else if (burnCD == 1) {
            currentHealth -= maxHealth * (5 / 100);
            isBurnt = false;
            burnCD--;
        }
    }

    if (isTaunt)
    {
        if (tauntCD == 3) {
            tauntCD--;
        }
        else if (tauntCD == 2) {
            tauntCD--;
        }
        else if (tauntCD == 1) {
            tauntCD--;
            isTaunt = false;
        }
    }

    if (isStun) {
        isStun = false;
    }
}

std::shared_ptr<Artefact> Kelpie::createDrop() {
    static std::random_device rd;
    static std::mt19937 rng(rd());
    std::uniform_real_distribution<float> dist(0.f, 100.f);

    float roll = dist(rng);

    if (roll < 10.f) {
        return nullptr;
    }
    else if (roll < 15.f) {
        return nullptr;
    }
    else if (roll < 17.f) {
        return nullptr;
    }
    else if (roll < 17.5f) {
        //return std::make_shared<Seaweed>();
        return nullptr;
    }
    return nullptr;
}