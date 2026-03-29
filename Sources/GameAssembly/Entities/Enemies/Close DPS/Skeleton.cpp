#include "Skeleton.h"
#include "../../Characters/Character.h"

Skeleton::Skeleton(int floor) {
    name = "Skeleton";
    entityClass = EClass::CLOSEDDPS;
    description = "Old pack of bones sticking together";
    biome = Biome::GRAVEYARD;

    level = floor;
    landing = floor / 5;

    finalArmor = 15.0f;
    finalPR = 30.0f;

    baseHealth = 25.0f;
    maxHealth = baseHealth * pow(1.1f, landing);
    currentHealth = maxHealth;

    baseAttackDamage = 40.0f;
    maxAttackDamage = baseAttackDamage * pow(1.1f, landing);
    currentAttackDamage = maxAttackDamage;

    baseAttackPower = 0.0f;
    maxAttackPower = baseAttackPower * pow(1.1f, landing);
    currentAttackPower = maxAttackPower;

    baseArmor = 0.1f;
    maxArmor = baseArmor * pow(1.1f, landing);
    currentArmor = maxArmor;

    basePowerResist = 0.2f;
    maxPowerResist = basePowerResist * pow(1.1f, landing);
    currentPowerResist = maxPowerResist;

    baseSpeed = 70.0f;
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

void Skeleton::Start() {}

void Skeleton::Update(float deltaTime) {}

void Skeleton::startTurn() {
    firstAbilityUp = true;
    if (CD2 == 0) { secondAbilityUp = true; } else { secondAbilityUp = false; }
    thirdAbilityUp = true;
    fourthAbilityUp = true;
}

void Skeleton::endTurn() {
    if (CD2 > 0) { CD2--; }
    // no manageeffect for third passive
}

bool Skeleton::entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies)
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

            if (availableChoices.empty()) return false;

            std::uniform_int_distribution<int> distChoice(0, availableChoices.size() - 1);
            int choice = availableChoices[distChoice(rng)];

            switch (choice)
            {
            case 1:
                firstAbility(*target);
                break;
            case 2:
                secondAbility();
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

void Skeleton::dropArtefacts() {

}

void Skeleton::firstAbility(Character& target) {
    float dmgDealt = currentAttackDamage * (1.0f - target.getCurrentArmor() / 100.0f);
    target.setCurrentHealth(std::max(0.0f, target.getCurrentHealth() - dmgDealt));
}

void Skeleton::secondAbility() {
    baseAttackDamage = baseAttackDamage + (baseAttackDamage * 10.0f / 100.0f);

    CD2 = 3;
}

void Skeleton::thirdAbility() {

}

void Skeleton::fourthAbility() {

}