#include "Brutus.h"

Brutus::Brutus()
{
    name = "Brutus";
    entityClass = EClass::RANGEDDPS;
    description = "Brutus is a man";

    baseHealth = 40;
    finalHP = 500;
    maxHealth = baseHealth + (finalHP - baseHealth) * ((level - 1) / (maxLevel - 1));
    currentHealth = baseHealth;

    baseAttackDamage = 8;
    finalAD = 325;
    maxAttackDamage = baseAttackDamage + (finalAD - baseAttackDamage) * ((level - 1) / (maxLevel - 1));
    currentAttackDamage = baseAttackDamage;

    baseAttackPower = 5;
    finalAP = 300;
    maxAttackPower = baseAttackPower + (finalAP - baseAttackPower) * ((level - 1) / (maxLevel - 1));
    currentAttackPower = baseAttackPower;

    baseArmor = 0.4;
    finalArmor = 15;
    maxArmor = baseArmor + (finalArmor - baseArmor) * ((level - 1) / (maxLevel - 1));
    currentArmor = baseArmor;

    basePowerResist = 0.2;
    finalPR = 10;
    maxPowerResist = basePowerResist + (finalPR - basePowerResist) * ((level - 1) / (maxLevel - 1));
    currentPowerResist = basePowerResist;

    baseSpeed = 80;
}

void Brutus::firstAbility(std::shared_ptr<Enemy>target)
{
    for (int i = 0; i < 3; i++)
    {
        float dmgDealt = currentAttackDamage - currentAttackDamage * (target->getCurrentArmor() / 100);
        target->setCurrentHealth(target->getCurrentHealth() - dmgDealt / 3);
    }

    CD1 = 1;
}

void Brutus::secondAbility(std::shared_ptr<Enemy>target)
{
    static std::random_device rd;
    static std::mt19937 rng(rd());
    std::uniform_int_distribution<int> arrows(5, 10);

    int arrowToShoot = arrows(rng);

    for (int i = 0; i < arrowToShoot; i++)
    {
        float dmgDealt = currentAttackDamage - currentAttackDamage * (target->getCurrentArmor() / 100);
        target->setCurrentHealth(target->getCurrentHealth() - dmgDealt / 3);
    }

    CD2 = 5;
}

void Brutus::thirdAbility(std::shared_ptr<Enemy>target)
{
    float dmgDealt = currentAttackDamage - currentAttackDamage * (target->getCurrentArmor() * 0.2 / 100 );
    target->setCurrentHealth(target->getCurrentHealth() - dmgDealt);

    CD3 = 6;
}

void Brutus::fourthAbility(std::shared_ptr<Enemy>target)
{
    float dmgAPDealt = currentAttackPower * 4 - currentAttackPower * (target->getCurrentPowerResist() / 100);
    float dmgADDealt = currentAttackDamage * 4 - currentAttackDamage * (target->getCurrentArmor() / 100);
    target->setCurrentHealth(target->getCurrentHealth() - (dmgADDealt + dmgAPDealt) / 2);

    CD4 = 11;
}

void Brutus::startTurn()
{
    if (CD1 == 0) { firstAbilityUp = true; } else { firstAbilityUp = false; }
    if (CD2 == 0 && level >= 5) { secondAbilityUp = true; } else { secondAbilityUp = false; }
    if (CD3 == 0 && level >= 18) { thirdAbilityUp = true; } else { thirdAbilityUp = false; }
    if (CD4 == 0 && level >= 37) { fourthAbilityUp = true; } else { fourthAbilityUp = false; }
}

void Brutus::endTurn()
{
    if (CD1 > 0) { CD1--; }
    if (CD2 > 0) { CD2--; }
    if (CD3 > 0) { CD3--; }
    if (CD4 > 0) { CD4--; }

    manageStatusEffect();

    selectedTarget = nullptr;
}

bool Brutus::entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies)
{
    switch (currentState) {
        case PlayerState::StartTurn : {
            startTurn();
            currentState = PlayerState::ChoosingAbility;
            break;
        }

        case PlayerState::ChoosingAbility : {
            ImGui::Begin("Choose Ability");

            ImGui::BeginDisabled(!firstAbilityUp);
            if (ImGui::Button("Triple Shoot"))
            {
                abilitySelected = 1;
                currentState = PlayerState::ChoosingTarget;
            }
            ImGui::EndDisabled();


            ImGui::BeginDisabled(!secondAbilityUp);
            if (ImGui::Button("Arrow's Storm"))
            {
                abilitySelected = 2;
                currentState = PlayerState::Acting;
            }
            ImGui::EndDisabled();


            ImGui::BeginDisabled(!thirdAbilityUp);
            if (ImGui::Button("Piercing Arrow"))
            {
                abilitySelected = 3;
                currentState = PlayerState::ChoosingTarget;
            }
            ImGui::EndDisabled();

            ImGui::BeginDisabled(!fourthAbilityUp);
            if (ImGui::Button("Explosive Arrow"))
            {
                abilitySelected = 4;
                currentState = PlayerState::ChoosingTarget;
            }
            ImGui::EndDisabled();

            ImGui::End();
            break;
        }

        case PlayerState::ChoosingTarget :
        {
            ImGui::Begin("Choose enemy target");
            for (int i = 0; i < enemies.size(); i++)
            {
                std::string label = enemies[i]->getName() + "##" + std::to_string(i);

                if (ImGui::Button(label.c_str())) {
                    selectedTarget = std::static_pointer_cast<Enemy>(enemies[i]);
                    currentState = PlayerState::Acting;
                }
            }

            if (ImGui::Button("Return")) {
                currentState = PlayerState::ChoosingAbility;
            }

            ImGui::End();
            break;
        }

        case PlayerState::Acting :
        {
            switch (abilitySelected) {
                case 1 : {
                    firstAbility(selectedTarget);
                    break;
                }
                case 2 : {
                    secondAbility(selectedTarget);
                    break;
                }
                case 3 : {
                    thirdAbility(selectedTarget);
                    break;
                }
                case 4 :
                {
                    fourthAbility(selectedTarget);
                    break;
                }
                default : {
                    currentState = PlayerState::ChoosingAbility;
                }

            }
            currentState = PlayerState::EndTurn;
            break;
        }

        case PlayerState::EndTurn : {
            endTurn();
            currentState = PlayerState::StartTurn;
            return true;
        }
    }
    return false;
}

void Brutus::Start()
{
    // Called once when the scene starts playing.
}

void Brutus::Update(float deltaTime)
{

}