#include "Bear.h"
#include "../../Characters/Character.h"

Bear::Bear(int floor) {
    name = "Bear";
    entityClass = EClass::TANK;
    description = "The bear is a massive brute, slow to anger but impossible to stop once it starts.";
    biome = Biome::FOREST;

    level = floor;
    landing = floor / 5;

    finalArmor = 80.0f;
    finalPR = 60.0f;

    baseHealth = 75.0f;
    maxHealth = baseHealth * pow(1.1f, landing);
    currentHealth = maxHealth;

    baseAttackDamage = 35.0f;
    maxAttackDamage = baseAttackDamage * pow(1.1f, landing);
    currentAttackDamage = maxAttackDamage;

    baseAttackPower = 10.0f;
    maxAttackPower = baseAttackPower * pow(1.1f, landing);
    currentAttackPower = maxAttackPower;

    baseArmor = 0.75f;
    maxArmor = baseArmor * pow(1.1f, landing);
    currentArmor = maxArmor;

    basePowerResist = 0.65f;
    maxPowerResist = basePowerResist * pow(1.1f, landing);
    currentPowerResist = maxPowerResist;

    baseSpeed = 100.0f;
    currentSpeed = baseSpeed;

    baseExpDrop = 30.0f;
    maxExpDrop = 1200.0f;
    float t = std::min(landing / 100.0f, 1.0f);
    currentExpDrop = baseExpDrop + (maxExpDrop - baseExpDrop) * t;

    poisonCD = 0;
    burnCD = 0;
    tauntCD = 0;
    isStun = false;
}

void Bear::Start() {}

void Bear::Update(float deltaTime) {}

void Bear::startTurn() {
    firstAbilityUp = true;
    if (CD2 == 0) { secondAbilityUp = true; } else { secondAbilityUp = false; }
    thirdAbilityUp = true;
    if (CD4 == 0 && level > 50) { fourthAbilityUp = true; } else { fourthAbilityUp = false; }
}

void Bear::endTurn() {
    if (CD2 > 0) { CD2--; }
    if (CD4 > 0) { CD4--; }

    manageStatusEffect();
}

bool Bear::entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies)
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

            Character* target = nullptr;

            for (auto& c : characters)
            {
                Character* t = dynamic_cast<Character*>(c.get());
                if (t && t->getClass() == EClass::TANK)
                {
                    target = t;
                    break;
                }
            }

            if (!target)
            {
                std::uniform_int_distribution<int> distTarget(0, characters.size() - 1);
                target = dynamic_cast<Character*>(characters[distTarget(rng)].get());
            }

            if (!target) return false;

            std::uniform_int_distribution<int> distChoice(1, 3);
            int choice = distChoice(rng);

            switch (choice)
            {
            case 1:
                firstAbility(*target);
                break;
            case 2:
                secondAbility();
                break;
            case 3:
                {
                    fourthAbility(*target);
                    break;
                }
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

void Bear::dropArtefacts() {

}

void Bear::firstAbility(Character& target) { // powerAbilityOne=0.9f
    float dmgDealt = currentAttackDamage * (1.0f - target.getCurrentArmor() / 100.0f);
    target.setCurrentHealth(std::max(0.0f, target.getCurrentHealth() - dmgDealt * powerAbilityOne));
}

void Bear::secondAbility() {
    currentHealth = currentHealth + maxHealth * 0.15f;

    CD2 = 3;
}

void Bear::thirdAbility() {
    // done in entityTurn
}

void Bear::fourthAbility(Character& target) {
    currentArmor = currentArmor + currentArmor * 0.05f;
    currentPowerResist = currentPowerResist + currentPowerResist * 0.05f;

    target.setIsTaunt(true);
    setTauntCD(3);

    CD4 = 7;
}