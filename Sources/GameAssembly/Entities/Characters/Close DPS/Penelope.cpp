#include "Penelope.h"

Penelope::Penelope()
{
    name = "Penelope";
    entityClass = EClass::ASSASSIN;
    description = "Penelope is a woman";

    baseHealth = 25;
    finalHP = 300;
    maxHealth = baseHealth + (finalHP - baseHealth) * ((level - 1) / (maxLevel - 1));
    currentHealth = maxHealth;

    baseAttackDamage = 15;
    finalAD = 450;
    maxAttackDamage = baseAttackDamage + (finalAD - baseAttackDamage) * ((level - 1) / (maxLevel - 1));
    currentAttackDamage = baseAttackDamage;

    baseAttackPower = 0;
    finalAP = 0;
    maxAttackPower = 0;
    currentAttackPower = 0;

    baseArmor = 0.5f;
    finalArmor = 15;
    maxArmor = baseArmor + (finalArmor - baseArmor) * ((level - 1) / (maxLevel - 1));
    currentArmor = baseArmor;

    basePowerResist = 1;
    finalPR = 20;
    maxPowerResist = basePowerResist + (finalPR - basePowerResist) * ((level - 1) / (maxLevel - 1));
    currentPowerResist = basePowerResist;

    baseSpeed = 62.5;

    fourthAbilityActive = false;
}

void Penelope::firstAbility(std::shared_ptr<Enemy>target)
{
    float dmgDealt = currentAttackDamage - currentAttackDamage * (target->getCurrentArmor() / 100);
    target->setCurrentHealth(target->getCurrentHealth() - dmgDealt);

    CD1 = 1;
}

void Penelope::secondAbility(std::shared_ptr<Enemy>target)
{
    target->setIsPoisoned(true);
    target->setPoisonCD(5);

    CD2 = 3;
}

void Penelope::thirdAbility(std::shared_ptr<Enemy>target)
{
    float dmgDealt = currentAttackDamage * 2 - currentAttackDamage * (target->getCurrentArmor() / 100);
    target->setCurrentHealth(target->getCurrentHealth() - dmgDealt);
    currentHealth += dmgDealt * (80 / 100);

    CD3 = 4;
}

void Penelope::startTurn()
{
    if (CD1 == 0) { firstAbilityUp = true; } else { firstAbilityUp = false; }
    if (CD2 == 0 && level >= 8) { secondAbilityUp = true; } else { secondAbilityUp = false; }
    if (CD3 == 0 && level >= 20) { thirdAbilityUp = true; } else { thirdAbilityUp = false; }
    if (level >= 45) fourthAbilityActive = true;
}

void Penelope::endTurn()
{
    if (CD1 > 0) { CD1--; }
    if (CD2 > 0) { CD2--; }
    if (CD3 > 0) { CD3--; }

    manageStatusEffect();

    selectedTarget = nullptr;
}

bool Penelope::entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies)
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
            if (ImGui::Button("Cut"))
            {
                abilitySelected = 1;
                currentState = PlayerState::ChoosingTarget;
            }
            ImGui::EndDisabled();


            ImGui::BeginDisabled(!secondAbilityUp);
            if (ImGui::Button("Poison"))
            {
                abilitySelected = 2;
                currentState = PlayerState::Acting;
            }
            ImGui::EndDisabled();


            ImGui::BeginDisabled(!thirdAbilityUp);
            if (ImGui::Button("Vampiric Cut"))
            {
                abilitySelected = 3;
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

void Penelope::Start()
{
    // Called once when the scene starts playing.
}

void Penelope::Update(float deltaTime)
{

}