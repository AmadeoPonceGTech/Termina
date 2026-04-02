#include "Gargoyle.h"
#include "../../Characters/Character.h"

Gargoyle::Gargoyle(int floor) {
    name = "Gargoyle";
    entityClass = EClass::BOSS;
    description = "Gargoyle, this monster of stone, inspiring fear, jumps on his enemies.";
    biome = Biome::GRAVEYARD;

    level = floor;
    landing = floor / 5;

    finalArmor = 30.0f;
    finalPR = 30.0f;

    baseHealth = 80.0f;
    maxHealth = baseHealth * pow(1.1f, landing);
    currentHealth = maxHealth;

    baseAttackDamage = 70.0f;
    maxAttackDamage = baseAttackDamage * pow(1.1f, landing);
    currentAttackDamage = maxAttackDamage;

    baseAttackPower = 70.0f;
    maxAttackPower = baseAttackPower * pow(1.1f, landing);
    currentAttackPower = maxAttackPower;

    baseArmor = 0.2f;
    maxArmor = baseArmor * pow(1.1f, landing);
    currentArmor = maxArmor;

    basePowerResist = 0.2f;
    maxPowerResist = basePowerResist * pow(1.1f, landing);
    currentPowerResist = maxPowerResist;

    baseSpeed = 100.0f;
    currentSpeed = baseSpeed;

    baseExpDrop = 50.0f;
    maxExpDrop = 1500.0f;
    float t = std::min(landing / 100.0f, 1.0f);
    currentExpDrop = baseExpDrop + (maxExpDrop - baseExpDrop) * t;

    poisonCD = 0;
    burnCD = 0;
    tauntCD = 0;
    isStun = false;
}

void Gargoyle::Start() {}

void Gargoyle::Update(float deltaTime) {}

void Gargoyle::startTurn() {
    firstAbilityUp = true;

    isPoisoned = false;
    isBurnt = false;
    isStun = false;
    isTaunt = false;

    poisonCD = 0;
    burnCD = 0;
    tauntCD = 0;
    isStun = false;
}

void Gargoyle::endTurn() {
    isPoisoned = false;
    isBurnt = false;
    isStun = false;
    isTaunt = false;

    poisonCD = 0;
    burnCD = 0;
    tauntCD = 0;
    isStun = false;
}

bool Gargoyle::entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies)
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

            if (availableAbilities.empty()) return false;

            std::uniform_int_distribution<int> distChoice(0, availableAbilities.size() - 1);
            int choice = availableAbilities[distChoice(rng)];

            switch (choice)
            {
            case 1:
                firstAbility(*target);
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

void Gargoyle::dropArtefacts() {

}

void Gargoyle::firstAbility(Character& target) {
    float dmgDealt = currentAttackPower * (1.0f - target.getCurrentPowerResist() / 100.0f);
    target.setCurrentHealth(std::max(0.0f, target.getCurrentHealth() - dmgDealt * powerAbilityOne));
}

void Gargoyle::secondAbility() {
}

void Gargoyle::thirdAbility() {
}

void Gargoyle::fourthAbility() {
}