#include "Eel.h"
#include "../../Characters/Character.h"

Eel::Eel(int floor) {
    name = "Eel";
    entityClass = EClass::ASSASSIN;
    description = "A sneaky fish slipping away when caught.";
    biome = Biome::OCEAN;

    level = floor;
    landing = floor / 5;

    finalArmor = 40.0f;
    finalPR = 40.0f;

    baseHealth = 25.0f;
    maxHealth = baseHealth * pow(1.1f, landing);
    currentHealth = maxHealth;

    baseAttackDamage = 10.0f;
    maxAttackDamage = baseAttackDamage * pow(1.1f, landing);
    currentAttackDamage = maxAttackDamage;

    baseAttackPower = 35.0f;
    maxAttackPower = baseAttackPower * pow(1.1f, landing);
    currentAttackPower = maxAttackPower;

    baseArmor = 0.2f;
    maxArmor = baseArmor * pow(1.1f, landing);
    currentArmor = maxArmor;

    basePowerResist = 0.2f;
    maxPowerResist = basePowerResist * pow(1.1f, landing);
    currentPowerResist = maxPowerResist;

    baseSpeed = 50.0f;
    currentSpeed = baseSpeed;

    baseExpDrop = 20.0f;
    maxExpDrop = 1000.0f;
    float t = std::min(landing / 100.0f, 1.0f);
    currentExpDrop = baseExpDrop + (maxExpDrop - baseExpDrop) * t;

    poisonCD = 0;
    burnCD = 0;
    tauntCD = 0;
    isStun = false;
}

void Eel::Start() {}

void Eel::Update(float deltaTime) {}

void Eel::startTurn() {
    firstAbilityUp = true;
    if (CD2 == 0) { secondAbilityUp = true; } else { secondAbilityUp = false; }
    if (CD3 == 0) { thirdAbilityUp = true; } else { thirdAbilityUp = false; }
    if (CD4 == 0 && level > 50) { fourthAbilityUp = true; } else { fourthAbilityUp = false; }
}

void Eel::endTurn() {
    if (CD2 > 0) { CD2--; }
    if (CD3 > 0) { CD3--; }
    if (CD4 > 0) { CD4--; }

    manageStatusEffect();
}

bool Eel::entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies)
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

            std::vector<int> availableAbilities;

            if (firstAbilityUp)  availableAbilities.push_back(1);
            if (secondAbilityUp) availableAbilities.push_back(2);
            if (thirdAbilityUp)  availableAbilities.push_back(3);
            if (fourthAbilityUp) availableAbilities.push_back(4);

            if (availableAbilities.empty()) return false;

            std::uniform_int_distribution<int> distChoice(0, availableAbilities.size() - 1);
            int choice = availableAbilities[distChoice(rng)];

            switch (choice)
            {
            case 1:
                firstAbility(*target);
                break;
            case 2:
                secondAbility();
                break;
            case 3:
                thirdAbility();
                break;
            case 4:
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

void Eel::dropArtefacts() {

}

void Eel::firstAbility(Character& target) {
    float dmgDealt = currentAttackDamage * (1.0f - target.getCurrentArmor() / 100.0f);
    target.setCurrentHealth(std::max(0.0f, target.getCurrentHealth() - dmgDealt));

    static std::random_device rd;
    static std::mt19937 rng(rd());
    std::uniform_int_distribution<int> proc(1, 100);

    if (proc(rng) <= 30) {
        float slow = 10.0f;
        target.setCurrentSpeed(std::max(0.0f, target.getCurrentSpeed() - slow));
    }
}

void Eel::secondAbility() {
    float buff = currentAttackDamage * 0.2f;
    currentAttackDamage += buff;
    CD2 = 4;
}

void Eel::thirdAbility() {
    poisonCD = 0;
    isPoisoned = false;
    burnCD = 0;
    isBurnt = false;
    tauntCD = 0;
    isTaunt = false;
    isStun = false;

    CD3 = 5;
}

void Eel::fourthAbility(Character& target) {
    float multiplier = (target.getCurrentHealth() < target.getMaxHealth() * 0.5f) ? 2.5f : 1.5f;
    float dmgDealt = currentAttackDamage * multiplier * (1.0f - target.getCurrentArmor() / 100.0f);
    target.setCurrentHealth(std::max(0.0f, target.getCurrentHealth() - dmgDealt));
    CD4 = 6;
}