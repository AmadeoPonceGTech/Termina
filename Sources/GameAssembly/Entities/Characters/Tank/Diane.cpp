#include "Diane.h"

Diane::Diane()
{
    name = "Diane";
    entityClass = EClass::TANK;
    description = "Diane, a fearless fighter, that doesn't hesitate to protect her fellow companions.";

    baseHealth = 100;
    finalHP = 1000;
    maxHealth = baseHealth + (finalHP - baseHealth) * ((level - 1) / (maxLevel - 1));
    currentHealth = baseHealth;

    baseAttackDamage = 2.5f;
    finalAD = 250;
    maxAttackDamage = baseAttackDamage + (finalAD - baseAttackDamage) * ((level - 1) / (maxLevel - 1));
    currentAttackDamage = baseAttackDamage;

    baseAttackPower = 20;
    finalAP = 200;
    maxAttackPower = baseAttackPower + (finalAP - baseAttackPower) * ((level - 1) / (maxLevel - 1));
    currentAttackPower = baseAttackPower;

    baseArmor = 5;
    finalArmor = 50;
    maxArmor = baseArmor + (finalArmor - baseArmor) * ((level - 1) / (maxLevel - 1));
    currentArmor = baseArmor;

    basePowerResist = 4;
    finalPR = 30;
    maxPowerResist = basePowerResist + (finalPR - basePowerResist) * ((level - 1) / (maxLevel - 1));
    currentPowerResist = basePowerResist;

    baseSpeed = 100;
    currentSpeed = baseSpeed;
}

void Diane::firstAbility(std::shared_ptr<Enemy>target)
{
    float dmgDealt = currentAttackDamage - currentAttackDamage * (target->getCurrentArmor() / 100);
    target->setCurrentHealth(target->getCurrentHealth() - dmgDealt);

    if (artefact) {
        artefact->onInflictedDamage(*this);
    }

    CD1 = 1;
}

void Diane::secondAbility(std::shared_ptr<Enemy>target)
{
    target->setIsTaunt(true);
    target->setTauntCD(3);

    CD2 = 6;
}

void Diane::thirdAbility(std::shared_ptr<Character>target)
{
    shield += currentAttackPower;
    target->setShield(target->getShield() + currentAttackPower);

    CD3 = 4;
}

void Diane::fourthAbility(std::vector<std::shared_ptr<Entity>> &targets)
{
    for (auto character : targets) {
        if (character->getName() == getName()) {
            currentArmor = currentArmor * 1.3;
        }
        else {
            character->setCurrentArmor(character->getCurrentArmor() * 1.2);
        }
    }

}

void Diane::startRun(std::vector<std::shared_ptr<Entity>> &targets)
{
    if (level >= 40){ fourthAbility(targets); }
}

void Diane::startTurn()
{
    if (CD1 == 0) { firstAbilityUp = true; } else { firstAbilityUp = false; }
    if (CD2 == 0 && level >= 10) { secondAbilityUp = true; } else { secondAbilityUp = false; }
    if (CD3 == 0 && level >= 25) { thirdAbilityUp = true; } else { thirdAbilityUp = false; }
}

void Diane::endTurn()
{
    if (CD1 > 0) { CD1--; }
    if (CD2 > 0) { CD2--; }
    if (CD3 > 0) { CD3--; }
    if (CD4 > 0) { CD4--; }

    manageStatusEffect();

    selectedTargetE = nullptr;
    selectedTargetC = nullptr;
}

bool Diane::entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies)
{
    switch (currentState) {
        case PlayerState::STARTTURN : {
            startTurn();

            if (artefact && !artefactAlreadyUsed) {
                artefact->ActingArtefact(*this);
                artefactAlreadyUsed = true;
            }

            currentState = PlayerState::CHOOSINGABILITY;
            break;
        }

        case PlayerState::CHOOSINGABILITY : {
            ImGui::Begin("Choose Ability");

            ImGui::BeginDisabled(!firstAbilityUp);
            if (ImGui::Button("Shield Charge"))
            {
                abilitySelected = 1;
                currentState = PlayerState::CHOOSINGTARGET;
            }
            ImGui::EndDisabled();


            ImGui::BeginDisabled(!secondAbilityUp);
            if (ImGui::Button("Taunt"))
            {
                abilitySelected = 2;
                currentState = PlayerState::ACTING;
            }
            ImGui::EndDisabled();


            ImGui::BeginDisabled(!thirdAbilityUp);
            if (ImGui::Button("Shield Buff"))
            {
                abilitySelected = 3;
                currentState = PlayerState::CHOOSINGTARGET;
            }
            ImGui::EndDisabled();

            ImGui::End();
            break;
        }

        case PlayerState::CHOOSINGTARGET :
        {
            if (abilitySelected == 1 or abilitySelected == 2)
            {
                ImGui::Begin("Choose enemy target");
                for (int i = 0; i < enemies.size(); i++)
                {
                    std::string label = enemies[i]->getName() + "##" + std::to_string(i);

                    if (ImGui::Button(label.c_str())) {
                        selectedTargetE = std::static_pointer_cast<Enemy>(enemies[i]);
                        currentState = PlayerState::ACTING;
                    }
                }

                if (ImGui::Button("Return")) {
                    currentState = PlayerState::CHOOSINGABILITY;
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
                        currentState = PlayerState::ACTING;
                    }
                }

                if (ImGui::Button("Return")) {
                    currentState = PlayerState::CHOOSINGABILITY;
                }

                ImGui::End();
            }
            break;
        }

        case PlayerState::ACTING :
        {
            switch (abilitySelected) {
                case 1 : {
                    firstAbility(selectedTargetE);
                    break;
                }
                case 2 : {
                    secondAbility(selectedTargetE);
                    break;
                }
                case 3 : {
                    thirdAbility(selectedTargetC);
                    break;
                }
                default : {
                    currentState = PlayerState::CHOOSINGABILITY;
                }

            }
            currentState = PlayerState::ENDTURN;
            break;
        }

        case PlayerState::ENDTURN : {
            endTurn();

            if (artefact) {
                artefact->ActingArtefactEveryTurns(*this);
            }

            currentState = PlayerState::STARTTURN;
            return true;
        }
    }
    return false;
}

void Diane::Start() {}

void Diane::Update(float deltaTime) {}