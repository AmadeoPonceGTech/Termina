#include "AdeptOfTheChaos.h"
#include "../../Characters/Character.h"

AdeptOfTheChaos::AdeptOfTheChaos(int floor) {
    name = "AdeptOfTheChaos";
    entityClass = EClass::RANGEDDPS;
    description = "He's dark, his mind is tortured and he will avenge all of his losses.";
    biome = Biome::GRAVEYARD;

    level = floor;
    landing = floor / 5;

    finalArmor = 40.0f;
    finalPR = 50.0f;

    baseHealth = 20.0f;
    maxHealth = baseHealth * pow(1.1f, landing);
    currentHealth = maxHealth;

    baseAttackDamage = 0.0f;
    maxAttackDamage = baseAttackDamage * pow(1.1f, landing);
    currentAttackDamage = maxAttackDamage;

    baseAttackPower = 25.0f;
    maxAttackPower = baseAttackPower * pow(1.1f, landing);
    currentAttackPower = maxAttackPower;

    baseArmor = 0.2f;
    maxArmor = baseArmor * pow(1.1f, landing);
    currentArmor = maxArmor;

    basePowerResist = 0.2f;
    maxPowerResist = basePowerResist * pow(1.1f, landing);
    currentPowerResist = maxPowerResist;

    baseSpeed = 80.0f;
    currentSpeed = baseSpeed;

    baseExpDrop = 30.0f;
    maxExpDrop = 1300.0f;
    float t = std::min(landing / 100.0f, 1.0f);
    currentExpDrop = baseExpDrop + (maxExpDrop - baseExpDrop) * t;

    poisonCD = 0;
    burnCD = 0;
    tauntCD = 0;
    isStun = false;
}

void AdeptOfTheChaos::Start() {}

void AdeptOfTheChaos::Update(float deltaTime) {}

void AdeptOfTheChaos::startTurn() {
    firstAbilityUp = true;
    if (CD2 == 0) { secondAbilityUp = true; } else { secondAbilityUp = false; }
    thirdAbilityUp = true;
    if (CD4 == 0 && level > 50) { fourthAbilityUp = true; } else { fourthAbilityUp = false; }
}

void AdeptOfTheChaos::endTurn() {
    if (CD2 > 0) { CD2--; }
    if (CD4 > 0) { CD4--; }

    manageStatusEffect();
}

bool AdeptOfTheChaos::entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies)
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

            std::uniform_int_distribution<int> distChoice(1, 4);
            int choice = distChoice(rng);

            switch (choice)
            {
            case 1:
                firstAbility(*target);
                break;
            case 2:
                secondAbility(*target);
                break;
            case 3:
                {
                    thirdAbility();
                    break;
                }
            case 4:
                {
                    std::vector<Character*> targets;
                    for (auto& c : characters)
                    {
                        auto* t = dynamic_cast<Character*>(c.get());
                        if (t) targets.push_back(t);
                    }
                    fourthAbility(targets);
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

void AdeptOfTheChaos::dropArtefacts() {

}

void AdeptOfTheChaos::firstAbility(Character& target) {
    float dmgDealt = currentAttackDamage * (1.0f - target.getCurrentArmor() / 100.0f);
    target.setCurrentHealth(std::max(0.0f, target.getCurrentHealth() - dmgDealt * powerAbilityOne));
}

void AdeptOfTheChaos::secondAbility(Character& target) {
    float dmgDealt = currentAttackDamage * (1.0f - target.getCurrentArmor() / 100.0f);
    target.setCurrentHealth(std::max(0.0f, target.getCurrentHealth() - dmgDealt * powerAbilityTwo));

    CD2 = 3;
}

void AdeptOfTheChaos::thirdAbility() {
    currentHealth = currentHealth - (maxHealth * 15.0f / 100.0f);
    currentAttackPower = currentAttackPower + (currentAttackPower * 10.0f / 100.0f);

    CD3 = 4;
}

void AdeptOfTheChaos::fourthAbility(const std::vector<Character*>& targets) {
    for (auto& target : targets)
    {
        float dmgDealt = currentAttackDamage * (1.0f - target->getCurrentArmor() / 100.0f);
        target->setCurrentHealth(std::max(0.0f, target->getCurrentHealth() - dmgDealt * powerAbilityFour));
    }

    CD4 = 7;
}