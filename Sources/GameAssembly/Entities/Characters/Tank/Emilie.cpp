#include "Emilie.h"

#include <algorithm>
#include <memory>

Emilie::Emilie()
{
    name = "Emilie";
    entityClass = EClass::TANK;
    description = "Emilie has worked her whole life in a forge, it gave her an unbreakable skin and preeminent muscles that allows her to be a great defender for her team.";

    baseHealth = 90;
    finalHP = 900;
    maxHealth = baseHealth + (finalHP - baseHealth) * ((level - 1) / (maxLevel - 1));
    currentHealth = baseHealth;

    baseAttackDamage = 0;
    finalAD = 0;
    maxAttackDamage = 0;
    currentAttackDamage = 0;

    baseAttackPower = 5;
    finalAP = 300;
    maxAttackPower = baseAttackPower + (finalAP - baseAttackPower) * ((level - 1) / (maxLevel - 1));
    currentAttackPower = baseAttackPower;

    baseArmor = 2;
    finalArmor = 20;
    maxArmor = baseArmor + (finalArmor - baseArmor) * ((level - 1) / (maxLevel - 1));
    currentArmor = baseArmor;

    basePowerResist = 5;
    finalPR = 50;
    maxPowerResist = basePowerResist + (finalPR - basePowerResist) * ((level - 1) / (maxLevel - 1));
    currentPowerResist = basePowerResist;

    baseSpeed = 95;
    currentSpeed = baseSpeed;
}

void Emilie::firstAbility(std::shared_ptr<Enemy>target, std::shared_ptr<Enemy>target2, std::shared_ptr<Enemy>target3, std::shared_ptr<Enemy>target4)
{
    if (target != nullptr){
        float dmgDealt = currentAttackDamage - currentAttackDamage * (target->getCurrentArmor() / 100);
        target->setCurrentHealth(target->getCurrentHealth() - dmgDealt / 3);
    }

    if (target2 != nullptr) {
        float dmgDealt2 = currentAttackDamage - currentAttackDamage * (target2->getCurrentArmor() / 100);
        target2->setCurrentHealth(target2->getCurrentHealth() - dmgDealt2 / 3);
    }

    if (target3 != nullptr) {
        float dmgDealt3 = currentAttackDamage - currentAttackDamage * (target3->getCurrentArmor() / 100);
        target3->setCurrentHealth(target3->getCurrentHealth() - dmgDealt3 / 3);
    }

    if (target4 != nullptr) {
        float dmgDealt4 = currentAttackDamage - currentAttackDamage * (target4->getCurrentArmor() / 100);
        target4->setCurrentHealth(target4->getCurrentHealth() - dmgDealt4 / 3);
    }

    CD1 = 1;
}

void Emilie::secondAbility(std::shared_ptr<Character> target)
{
    target->setCurrentPowerResist(target->getCurrentPowerResist() + maxPowerResist / 2);

    CD2 = 5;
}

void Emilie::thirdAbility(std::shared_ptr<Enemy>target, std::shared_ptr<Enemy>target2, std::shared_ptr<Enemy>target3, std::shared_ptr<Enemy>target4)
{
    float dmgDealt = currentAttackDamage - currentAttackDamage * (target->getCurrentArmor() / 100);
    target->setCurrentHealth(target->getCurrentHealth() - dmgDealt / 4);
    target->setIsStun(true);

    float dmgDealt2 = currentAttackDamage - currentAttackDamage * (target2->getCurrentArmor() / 100);
    target2->setCurrentHealth(target2->getCurrentHealth() - dmgDealt2 / 4);
    target->setIsStun(true);

    float dmgDealt3 = currentAttackDamage - currentAttackDamage * (target3->getCurrentArmor() / 100);
    target3->setCurrentHealth(target3->getCurrentHealth() - dmgDealt3 / 4);
    target->setIsStun(true);

    float dmgDealt4 = currentAttackDamage - currentAttackDamage * (target4->getCurrentArmor() / 100);
    target4->setCurrentHealth(target4->getCurrentHealth() - dmgDealt4 / 4);
    target->setIsStun(true);

    CD3 = 5;
}

bool Emilie::canBeAttacked(std::shared_ptr<Enemy> target)
{
    if (std::find(currentEnemies.begin(), currentEnemies.end(), target) != currentEnemies.end() and level >= 45)
    {
        currentEnemies.erase(std::find(currentEnemies.begin(), currentEnemies.end(), target));
        return false;
    }
    return true;
}

void Emilie::startTurn()
{
    if (CD1 == 0) { firstAbilityUp = true; } else { firstAbilityUp = false; }
    if (CD2 == 0 && level >= 6) { secondAbilityUp = true; } else { secondAbilityUp = false; }
    if (CD3 == 0 && level >= 20) { thirdAbilityUp = true; } else { thirdAbilityUp = false; }
}

void Emilie::endTurn()
{
    if (CD1 > 0) { CD1--; }
    if (CD2 > 0) { CD2--; }
    if (CD3 > 0) { CD3--; }

    manageStatusEffect();

    selectedTargetE = nullptr;
    selectedTargetC = nullptr;
}

bool Emilie::entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies)
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
            if (ImGui::Button("Shield Charge"))
            {
                abilitySelected = 1;
                currentState = PlayerState::ChoosingTarget;
            }
            ImGui::EndDisabled();


            ImGui::BeginDisabled(!secondAbilityUp);
            if (ImGui::Button("Taunt"))
            {
                abilitySelected = 2;
                currentState = PlayerState::Acting;
            }
            ImGui::EndDisabled();


            ImGui::BeginDisabled(!thirdAbilityUp);
            if (ImGui::Button("Shield Buff"))
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
            if (abilitySelected == 1 or abilitySelected == 2)
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
                    std::shared_ptr<Enemy> target;
                    target = std::dynamic_pointer_cast<Enemy>(enemies[0]);
                    std::shared_ptr<Enemy> target2;
                    target2 = std::dynamic_pointer_cast<Enemy>(enemies[1]);
                    std::shared_ptr<Enemy> target3;
                    target3 = std::dynamic_pointer_cast<Enemy>(enemies[2]);
                    std::shared_ptr<Enemy> target4;
                    target4 = std::dynamic_pointer_cast<Enemy>(enemies[3]);
                    firstAbility(target, target2, target3, target4);
                    break;
                }
                case 2 : {
                    secondAbility(selectedTargetC);
                    break;
                }
                case 3 : {
                    std::shared_ptr<Enemy> target;
                    target = std::dynamic_pointer_cast<Enemy>(enemies[0]);
                    std::shared_ptr<Enemy> target2;
                    target2 = std::dynamic_pointer_cast<Enemy>(enemies[1]);
                    std::shared_ptr<Enemy> target3;
                    target3 = std::dynamic_pointer_cast<Enemy>(enemies[2]);
                    std::shared_ptr<Enemy> target4;
                    target4 = std::dynamic_pointer_cast<Enemy>(enemies[3]);
                    thirdAbility(target, target2, target3, target4);
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

void Emilie::startFight(std::vector<std::shared_ptr<Entity>>& enemies) {
    for (auto& enemy : enemies) {
        currentEnemies.push_back(std::dynamic_pointer_cast<Enemy>(enemy));
    }
}

void Emilie::endFight() {
    currentEnemies.clear();
}

void Emilie::Start()
{
    // Called once when the scene starts playing.
}

void Emilie::Update(float deltaTime)
{

}