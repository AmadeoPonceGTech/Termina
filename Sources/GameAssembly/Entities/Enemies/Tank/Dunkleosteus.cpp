#include "Dunkleosteus.h"
#include "../../Characters/Character.h"

Dunkleosteus::Dunkleosteus(int floor) {
    name = "Dunkleosteus";
    entityClass = EClass::TANK;
    description = "A prehistoric fish that scares everything since the night of the ages.";
    biome = Biome::OCEAN;

    level = floor;
    landing = floor / 5;

    finalArmor = 60.0f;
    finalPR = 60.0f;

    baseHealth = 85.0f;
    maxHealth = baseHealth * pow(1.1f, landing);
    currentHealth = maxHealth;

    baseAttackDamage = 20.0f;
    maxAttackDamage = baseAttackDamage * pow(1.1f, landing);
    currentAttackDamage = maxAttackDamage;

    baseAttackPower = 10.0f;
    maxAttackPower = baseAttackPower * pow(1.1f, landing);
    currentAttackPower = maxAttackPower;

    baseArmor = 0.65f;
    maxArmor = baseArmor * pow(1.1f, landing);
    currentArmor = maxArmor;

    basePowerResist = 0.65f;
    maxPowerResist = basePowerResist * pow(1.1f, landing);
    currentPowerResist = maxPowerResist;

    baseSpeed = 80.0f;
    currentSpeed = baseSpeed;

    baseExpDrop = 40.0f;
    maxExpDrop = 1300.0f;
    float t = std::min(landing / 100.0f, 1.0f);
    currentExpDrop = baseExpDrop + (maxExpDrop - baseExpDrop) * t;

    poisonCD = 0;
    burnCD = 0;
    tauntCD = 0;
    isStun = false;
}

void Dunkleosteus::Start() {}

void Dunkleosteus::Update(float deltaTime) {}

void Dunkleosteus::startTurn() {
    firstAbilityUp = true;
    if (CD2 == 0) { secondAbilityUp = true; } else { secondAbilityUp = false; }
    thirdAbilityUp = true;
    if (CD4 == 0 && level > 50) { fourthAbilityUp = true; } else { fourthAbilityUp = false; }
}

void Dunkleosteus::endTurn() {
    if (CD2 > 0) { CD2--; }
    if (CD4 > 0) { CD4--; }

    manageStatusEffect();
}

bool Dunkleosteus::entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies)
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
            Character* target2 = dynamic_cast<Character*>(characters[distTarget(rng)].get());
            if (!target) return false;

            std::uniform_int_distribution<int> distChoice(1, 3);
            int choice = distChoice(rng);

            switch (choice)
            {
            case 1:
                firstAbility(*target);
                break;
            case 2:
                secondAbility(*target, *target2);
                break;
            case 3:
                {

                    fourthAbility();
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

void Dunkleosteus::dropArtefacts() {

}

void Dunkleosteus::firstAbility(Character& target) {
    float multiplier = 1.0f;
    if (target.getClass() == EClass::ASSASSIN | target.getClass() == EClass::SUPPORT) { multiplier = 1.2f; }
    float dmgDealt = currentAttackDamage * (1.0f - target.getCurrentArmor() / 100.0f);
    target.setCurrentHealth(std::max(0.0f, target.getCurrentHealth() - dmgDealt * multiplier));
}

void Dunkleosteus::secondAbility(Character& target1, Character& target2) {
    float multiplier1 = 1.0f;
    if (target1.getClass() == EClass::ASSASSIN | target1.getClass() == EClass::SUPPORT) { multiplier1 = 1.2f; }
    float dmgDealt1 = currentAttackDamage * (1.0f - target1.getCurrentArmor() / 100.0f);
    target1.setCurrentHealth(std::max(0.0f, target1.getCurrentHealth() - dmgDealt1 * multiplier1));

    float multiplier2 = 1.0f;
    if (target2.getClass() == EClass::ASSASSIN | target2.getClass() == EClass::SUPPORT) { multiplier2 = 1.2f; }
    float dmgDealt2 = currentAttackDamage * (1.0f - target2.getCurrentArmor() / 100.0f);
    target2.setCurrentHealth(std::max(0.0f, target2.getCurrentHealth() - dmgDealt2 * multiplier2));

    CD2 = 4;
}

void Dunkleosteus::thirdAbility(Character& target) {

}

void Dunkleosteus::fourthAbility() {
    //Cast a wave who give a shield to all allies except self
    CD4 = 5;
}