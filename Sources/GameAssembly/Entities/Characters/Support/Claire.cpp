#include "Claire.h"

#include <random>

Claire::Claire()
{
    name = "Claire";
    entityClass = EClass::SUPPORT;
    description = "Claire; Her deep learning of magic is now put to action and make her a big support for her team. She doesn't bright by her bodily acts but by her intelligence.";

    baseHealth = 30;
    finalHP = 400;
    maxHealth = baseHealth + (finalHP - baseHealth) * ((level - 1) / (maxLevel - 1));
    currentHealth = baseHealth;

    baseAttackDamage = 3;
    finalAD = 100;
    maxAttackDamage = baseAttackDamage + (finalAD - baseAttackDamage) * ((level - 1) / (maxLevel - 1));
    currentAttackDamage = baseAttackDamage;

    baseAttackPower = 10;
    finalAP = 20;
    maxAttackPower = baseAttackPower + (finalAP - baseAttackPower) * ((level - 1) / (maxLevel - 1));
    currentAttackPower = baseAttackPower;

    baseArmor = 0.2;
    finalArmor = 10;
    maxArmor = baseArmor + (finalArmor - baseArmor) * ((level - 1) / (maxLevel - 1));
    currentArmor = baseArmor;

    basePowerResist = 0.4;
    finalPR = 10;
    maxPowerResist = basePowerResist + (finalPR - basePowerResist) * ((level - 1) / (maxLevel - 1));
    currentPowerResist = basePowerResist;

    baseSpeed = 80;
    currentSpeed = baseSpeed;
}

void Claire::firstAbility(std::shared_ptr<Enemy>target)
{
    float dmgDealt = currentAttackDamage - currentAttackDamage * (target->getCurrentArmor() / 100);
    target->setCurrentHealth(target->getCurrentHealth() - dmgDealt);

    if (artefact) {
        artefact->onInflictedDamage(*this);
    }

    static std::random_device rd;
    static std::mt19937 rng(rd());
    std::uniform_int_distribution<int> chance(1, 100);
    std::uniform_int_distribution<int> dist(1, 5);

    if (chance(rng) <= 15)
    {
        float choice = dist(rng);

        if (choice == 1) {
            target->setCurrentAttackDamage(target->getCurrentAttackDamage() - target->getCurrentAttackDamage() * 0.05);
        }
        else if (choice == 2) {
            target->setCurrentAttackPower(target->getCurrentAttackPower() - target->getCurrentAttackPower() * 0.05);
        }
        else if (choice == 3) {
            target->setCurrentArmor(target->getCurrentArmor() - target->getCurrentArmor() * 0.05);
        }
        else if (choice == 4) {
            target->setCurrentPowerResist(target->getCurrentPowerResist() - target->getCurrentPowerResist() * 0.05);
        }
        else if (choice == 5) {
            target->setCurrentSpeed(target->getCurrentSpeed() + currentAttackPower);
        }
    }

    CD1 = 1;
}

void Claire::secondAbility(std::shared_ptr<Character>target)
{
    target->setCurrentArmor(target->getCurrentArmor() * 1.05);
    target->setCurrentPowerResist(target->getCurrentPowerResist() * 1.05);

    CD2 = 4;
}

void Claire::thirdAbility(std::shared_ptr<Enemy>target)
{
    target->setCurrentSpeed(target->getCurrentSpeed() + currentAttackPower);

    CD3 = 6;
}

void Claire::fourthAbility(std::shared_ptr<Character>target)
{
    target->setCurrentAttackPower(target->getCurrentAttackPower() * 1.1);
    target->setCurrentAttackDamage(target->getCurrentAttackDamage() * 1.1);
    target->setCurrentArmor(target->getCurrentArmor() * 1.1);
    target->setCurrentPowerResist(target->getCurrentPowerResist() * 1.1);
    target->setCurrentSpeed(target->getCurrentSpeed() - currentAttackPower);

    CD4 = 11;
}

void Claire::startTurn()
{
    if (CD1 == 0) { firstAbilityUp = true; } else { firstAbilityUp = false; }
    if (CD2 == 0 && level >= 8) { secondAbilityUp = true; } else { secondAbilityUp = false; }
    if (CD3 == 0 && level >= 16) { thirdAbilityUp = true; } else { thirdAbilityUp = false; }
    if (CD4 == 0 && level >= 25) { fourthAbilityUp = true; } else { fourthAbilityUp = false; }
}

void Claire::endTurn()
{
    if (CD1 > 0) { CD1--; }
    if (CD2 > 0) { CD2--; }
    if (CD3 > 0) { CD3--; }
    if (CD4 > 0) { CD4--; }

    manageStatusEffect();

    selectedTargetE = nullptr;
    selectedTargetC = nullptr;
}

bool Claire::entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies)
{
    switch (currentState) {
        case PlayerState::StartTurn : {
            startTurn();

            if (artefact && !artefactAlreadyUsed) {
                artefact->ActingArtefact(*this);
                artefactAlreadyUsed = true;
            }

            currentState = PlayerState::ChoosingAbility;
            break;
        }

        case PlayerState::ChoosingAbility : {
            ImGui::Begin("Choose Ability");

            ImGui::BeginDisabled(!firstAbilityUp);
            if (ImGui::Button("Wand Hit"))
            {
                abilitySelected = 1;
                currentState = PlayerState::ChoosingTarget;
            }
            ImGui::EndDisabled();


            ImGui::BeginDisabled(!secondAbilityUp);
            if (ImGui::Button("Defense Buff"))
            {
                abilitySelected = 2;
                currentState = PlayerState::Acting;
            }
            ImGui::EndDisabled();


            ImGui::BeginDisabled(!thirdAbilityUp);
            if (ImGui::Button("Slow Debuff"))
            {
                abilitySelected = 3;
                currentState = PlayerState::ChoosingTarget;
            }
            ImGui::EndDisabled();

            ImGui::BeginDisabled(!fourthAbilityUp);
            if (ImGui::Button("Mega Buff"))
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
            if (abilitySelected == 1 or abilitySelected == 3)
            {
                ImGui::Begin("Choose enemy target");
                for (int i = 0; i < enemies.size(); i++)
                {
                    std::string label = enemies[i]->getName() + "##" + std::to_string(i);

                    if (ImGui::Button(label.c_str())) {
                        selectedTargetE = std::static_pointer_cast<Enemy>(enemies[i]);
                        currentState = PlayerState::Acting;
                    }
                }

                if (ImGui::Button("Return")) {
                    currentState = PlayerState::ChoosingAbility;
                }

                ImGui::End();
            }
            else
            {
                ImGui::Begin("Choose ally target");
                for (int i = 0; i < characters.size(); i++)
                {
                    std::string label = characters[i]->getName() + "##" + std::to_string(i);

                    if (ImGui::Button(label.c_str())) {
                        selectedTargetC = std::static_pointer_cast<Character>(characters[i]);
                        currentState = PlayerState::Acting;
                    }
                }

                if (ImGui::Button("Return")) {
                    currentState = PlayerState::ChoosingAbility;
                }

                ImGui::End();
            }
            break;
        }

        case PlayerState::Acting :
        {
            switch (abilitySelected) {
                case 1 : {
                    firstAbility(selectedTargetE);
                    break;
                }
                case 2 : {
                    secondAbility(selectedTargetC);
                    break;
                }
                case 3 : {
                    thirdAbility(selectedTargetE);
                    break;
                }
                case 4 : {
                    fourthAbility(selectedTargetC);
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
                artefact->ActingArtefactEveryTurns(*this);
            }

            currentState = PlayerState::StartTurn;
            return true;
        }
    }
    return false;
}

void Claire::Start()
{
    // Called once when the scene starts playing.
}

void Claire::Update(float deltaTime)
{

}