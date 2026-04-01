#include "RunicDear.h"
#include "../../Characters/Character.h"

RunicDear::RunicDear(int floor) {
    name = "RunicDear";
    entityClass = EClass::BOSS;
    description = "RunicDear's description.";
    biome = Biome::FOREST;

    level = floor;
    landing = floor / 5;

    finalArmor = 40.0f;
    finalPR = 70.0f;

    baseHealth = 100.0f;
    maxHealth = baseHealth * pow(1.1f, landing);
    currentHealth = maxHealth;

    baseAttackDamage = 0.0f;
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

    baseExpDrop = 50.0f;
    maxExpDrop = 1700.0f;
    float t = std::min(landing / 100.0f, 1.0f);
    currentExpDrop = baseExpDrop + (maxExpDrop - baseExpDrop) * t;

    poisonCD = 0;
    burnCD = 0;
    tauntCD = 0;
    isStun = false;
}

void RunicDear::Start() {}

void RunicDear::Update(float deltaTime) {}

void RunicDear::startTurn() {
    firstAbilityUp = true;
    if (CD2 == 0) { secondAbilityUp = true; } else { secondAbilityUp = false; }
    thirdAbilityUp = true;
    if (CD4 == 0 && level > 50) { fourthAbilityUp = true; } else { fourthAbilityUp = false; }
}

void RunicDear::endTurn() {
    if (CD2 > 0) { CD2--; }
    if (CD4 > 0) { CD4--; }

    manageStatusEffect();
}

bool RunicDear::entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies)
{
    switch (enemyState)
    {
    case EnemyState::STARTTURN:
        startTurn();
        thirdAbility();
        enemyState = EnemyState::ACTING;
        break;

    case EnemyState::ACTING:
        {
            if (characters.empty()) return false;

            static std::random_device rd;
            static std::mt19937 rng(rd());

            std::uniform_int_distribution<int> distTarget(0, characters.size() - 1);
            Character* target = dynamic_cast<Character*>(characters[distTarget(rng)].get());
            Enemy* targetEnemy = dynamic_cast<Enemy*>(enemies[distTarget(rng)].get());
            if (!target) return false;
            if (!targetEnemy) return false;

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
                secondAbility(*target, *targetEnemy);
                break;
            case 3:
                {
                    std::vector<Character*> targets;
                    for (auto& c : characters)
                    {
                        Character* t = dynamic_cast<Character*>(c.get());
                        if (t) targets.push_back(t);
                    }
                    fourthAbility(targets);
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

void RunicDear::dropArtefacts() {

}

void RunicDear::firstAbility(Character& target) {
    float dmgDealt = currentAttackPower * (1.0f - target.getCurrentPowerResist() / 100.0f);
    target.setCurrentHealth(std::max(0.0f, target.getCurrentHealth() - dmgDealt));
}

void RunicDear::secondAbility(Character& target, Enemy& enemyTarget) {
    float dmgDealt = currentAttackPower * (1.0f - target.getCurrentPowerResist() / 100.0f);
    target.setCurrentHealth(std::max(0.0f, target.getCurrentHealth() - dmgDealt));

    enemyTarget.setCurrentSpeed(enemyTarget.getCurrentSpeed() + (target.getCurrentSpeed() * 15.0f / 100.0f));
    CD2 = 3;
}

void RunicDear::thirdAbility() {
    currentArmor = currentArmor + (currentArmor * 5.0f / 100.0f);
    currentPowerResist = currentPowerResist + (currentPowerResist * 5.0f / 100.0f);
}

void RunicDear::fourthAbility(const std::vector<Character*>& targets) {
    for (auto character : targets) {
        float dmgDealt = currentAttackPower * (1.0f - character->getCurrentPowerResist() / 100.0f);
        character->setCurrentHealth(std::max(0.0f, character->getCurrentHealth() - dmgDealt));
    }

    CD4 = 7;
}