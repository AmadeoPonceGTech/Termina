#include "Edward.h"

Edward::Edward()
{
    name = "Edward";
    entityClass = EClass::RANGEDDPS;
    description = "Edward, cast powerful spells among the enemies to inflict them terrible magic induced injuries.";

    baseHealth = 20;
    finalHP = 250;
    maxHealth = baseHealth + (finalHP - baseHealth) * ((level - 1) / (maxLevel - 1));
    currentHealth = baseHealth;

    baseAttackDamage = 0;
    finalAD = 0;
    maxAttackDamage = 0;
    currentAttackDamage = 0;

    baseAttackPower = 20;
    finalAP = 200;
    maxAttackPower = baseAttackPower + (finalAP - baseAttackPower) * ((level - 1) / (maxLevel - 1));
    currentAttackPower = baseAttackPower;

    baseArmor = 0.25;
    finalArmor = 10;
    maxArmor = baseArmor + (finalArmor - baseArmor) * ((level - 1) / (maxLevel - 1));
    currentArmor = baseArmor;

    basePowerResist = 0.25;
    finalPR = 10;
    maxPowerResist = basePowerResist + (finalPR - basePowerResist) * ((level - 1) / (maxLevel - 1));
    currentPowerResist = basePowerResist;

    baseSpeed = 75;
    currentSpeed = baseSpeed;
}

void Edward::firstAbility(std::shared_ptr<Enemy>target)
{
    float dmgDealt = currentAttackPower - currentAttackPower * (target->getCurrentPowerResist() / 100);
    target->setCurrentHealth(target->getCurrentHealth() - dmgDealt);
    LogManager::getInstance().addLog("Edward uses \"Ember\"." + target->getName() + " takes damages.", ImVec4(0.6f, 0.85f, 0.6f, 1.0f));

    if (artefact) {
        artefact->onInflictedDamage(*this);
    }

    CD1 = 1;
}

void Edward::secondAbility(std::shared_ptr<Enemy>target)
{
    float dmgDealt = currentAttackPower * 2 - currentAttackPower * (target->getCurrentPowerResist() / 100);
    target->setCurrentHealth(target->getCurrentHealth() - dmgDealt);
    target->setIsBurnt(true);
    target->setBurnCD(3);
    LogManager::getInstance().addLog("Edward uses \"Fireball\"." + target->getName() + " takes damages and is burnt.", ImVec4(0.6f, 0.85f, 0.6f, 1.0f));

    if (artefact) {
        artefact->onInflictedDamage(*this);
    }

    CD2 = 3;
}

void Edward::thirdAbility(std::shared_ptr<Enemy>target)
{
    target->setIsStun(true);
    LogManager::getInstance().addLog("Edward uses \"Stun Spell\"." + target->getName() + " is stunned.", ImVec4(0.6f, 0.85f, 0.6f, 1.0f));

    CD3 = 5;
}

void Edward::fourthAbility(std::shared_ptr<Enemy>target)
{
    float dmgDealt = currentAttackPower * 4 - currentAttackPower * (target->getCurrentPowerResist() / 100);
    target->setCurrentHealth(target->getCurrentHealth() - dmgDealt);
    target->setIsBurnt(true);
    target->setBurnCD(3);
    LogManager::getInstance().addLog("Edward uses \"Magic Meteor\"." + target->getName() + " takes damages and is burnt.", ImVec4(0.6f, 0.85f, 0.6f, 1.0f));

    if (artefact) {
        artefact->onInflictedDamage(*this);
    }

    CD4 = 7;
}

void Edward::startTurn()
{
    if (CD1 == 0) { firstAbilityUp = true; } else { firstAbilityUp = false; }
    if (CD2 == 0 && level >= 10) { secondAbilityUp = true; } else { secondAbilityUp = false; }
    if (CD3 == 0 && level >= 20) { thirdAbilityUp = true; } else { thirdAbilityUp = false; }
    if (CD4 == 0 && level >= 36) { fourthAbilityUp = true; } else { fourthAbilityUp = false; }
}

void Edward::endTurn()
{
    if (CD1 > 0) { CD1--; }
    if (CD2 > 0) { CD2--; }
    if (CD3 > 0) { CD3--; }
    if (CD4 > 0) { CD4--; }

    manageStatusEffect();

    selectedTarget = nullptr;
}

bool Edward::entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies)
{
    switch (currentState) {
        case PlayerState::StartTurn : {
            startTurn();

            if (artefact && !artefactAlreadyUsed) {
                artefact->actingArtefact(*this);
                artefactAlreadyUsed = true;
            }

            currentState = PlayerState::ChoosingAbility;
            break;
        }

        case PlayerState::ChoosingAbility : {
            ImGui::Begin("Choose Ability");

            ImGui::BeginDisabled(!firstAbilityUp);
            if (ImGui::Button("Ember"))
            {
                abilitySelected = 1;
                currentState = PlayerState::ChoosingTarget;
            }
            ImGui::EndDisabled();


            ImGui::BeginDisabled(!secondAbilityUp);
            if (ImGui::Button("Fireball"))
            {
                abilitySelected = 2;
                currentState = PlayerState::Acting;
            }
            ImGui::EndDisabled();


            ImGui::BeginDisabled(!thirdAbilityUp);
            if (ImGui::Button("Stun Spell"))
            {
                abilitySelected = 3;
                currentState = PlayerState::ChoosingTarget;
            }
            ImGui::EndDisabled();

            ImGui::BeginDisabled(!fourthAbilityUp);
            if (ImGui::Button("Magic Meteor"))
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
                case 4 : {
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

            if (artefact) {
                artefact->actingArtefactEveryTurns(*this);
            }

            currentState = PlayerState::StartTurn;
            return true;
        }
    }
    return false;
}

void Edward::Start()
{
    // Called once when the scene starts playing.
}

void Edward::Update(float deltaTime)
{

}