#include "Game.h"

#include <iostream>
#include <ostream>

#include "../Termina/Renderer/Components/CameraComponent.hpp"
#include "../Termina/Renderer/Components/MeshComponent.hpp"
#include "../Termina/Scripting/API/ScriptableComponent.hpp"
#include "../Termina/World/Actor.hpp"

#include "../Entities/Characters/Close DPS/Alex.h"
#include "../Entities/Characters/Close DPS/Penelope.h"
#include "../Entities/Characters/Tank/Diane.h"
#include "../Entities/Characters/Tank/Emilie.h"
#include "../Entities/Characters/Support/Marcus.h"
#include "../Entities/Characters/Support/Claire.h"
#include "../Entities/Characters/Range DPS/Brutus.h"
#include "../Entities/Characters/Range DPS/Edward.h"


void Game::Start()
{
    if (!gameplay) {
        gameplay = std::make_unique<Gameplay>();
    }
    gameState = EGameState::Title;

#pragma region FillAllCharacters
    allCharacters.emplace_back(std::make_shared<Diane>());
    allCharacters.emplace_back(std::make_shared<Emilie>());
    allCharacters.emplace_back(std::make_shared<Claire>());
    allCharacters.emplace_back(std::make_shared<Marcus>());
    allCharacters.emplace_back(std::make_shared<Brutus>());
    allCharacters.emplace_back(std::make_shared<Edward>());
    allCharacters.emplace_back(std::make_shared<Alex>());
    allCharacters.emplace_back(std::make_shared<Penelope>());
#pragma endregion

    /////// Link Names -> Prefab
#pragma region MappingPrefab-Names
    p_Diane = TerminaScript::Prefab("Assets/Prefabs/Diane.trp");
    p_Emilie = TerminaScript::Prefab("Assets/Prefabs/Emilie.trp");
    p_Claire = TerminaScript::Prefab("Assets/Prefabs/Claire.trp");
    p_Marcus = TerminaScript::Prefab("Assets/Prefabs/Marcus.trp");
    p_Brutus = TerminaScript::Prefab("Assets/Prefabs/Brutus.trp");
    p_Edward = TerminaScript::Prefab("Assets/Prefabs/Edward.trp");
    p_Alex = TerminaScript::Prefab("Assets/Prefabs/Alex.trp");
    p_Penelope = TerminaScript::Prefab("Assets/Prefabs/Penelope.trp");

    characterPrefabMap["Diane"] = p_Diane;
    characterPrefabMap["Emilie"] = p_Emilie;
    characterPrefabMap["Claire"] = p_Claire;
    characterPrefabMap["Marcus"] = p_Marcus;
    characterPrefabMap["Brutus"] = p_Brutus;
    characterPrefabMap["Edward"] = p_Edward;
    characterPrefabMap["Alex"] = p_Alex;
    characterPrefabMap["Penelope"] = p_Penelope;
#pragma endregion
}

void Game::Update(float deltaTime)
{

    switch (gameState)
    {

        case EGameState::Title :
            ImGui::SetNextWindowSize(ImVec2(800, 800));
            ImGui::Begin("MainWindow");
            ImGui::Text("ENDLESS ROGUE");

            if (ImGui::Button("Play")) { gameState = EGameState::Menu; }

            ImGui::End();
            break;

        case EGameState::Menu :
        {

            ImGui::SetNextWindowSize(ImVec2(800, 800));
            ImGui::Begin("MainWindow");

            ImGui::Text("Select your characters");
            ImGui::SameLine();
            ImGui::BeginDisabled(!gameplay->teamIsComplete());
            if (ImGui::Button("Launch Run")) {
                gameState = EGameState::Run;
            };
            ImGui::EndDisabled();

            // ===== LAYOUT SIMPLE =====
            ImGui::Columns(2, nullptr, true);
            // ===== LEFT: LIST =====
            ImGui::BeginChild("CharacterList", ImVec2(0, 0), true);
            for (int i = 0; i < allCharacters.size(); i++) {
                if (ImGui::Selectable(allCharacters[i]->getName().c_str(), selectedCharacter == i)) {
                    selectedCharacter = i;
                }
            }

            ImGui::EndChild();
            ImGui::NextColumn();

            // ===== RIGHT: DETAILS =====
            ImGui::BeginChild("CharacterDetails", ImVec2(0, 0), true);

            if (selectedCharacter != -1) {
                auto& character = allCharacters[selectedCharacter];

                ImGui::Text("Character: %s", character->getName().c_str());
                ImGui::Dummy(ImVec2(0,10));
                ImGui::Text("Level : %i", character->getLevel());
                ImGui::Dummy(ImVec2(0,5));
                ImGui::Text("XP : %.1f       XPNeeded : %.1f       %.2f %%", character->getCurrentXP(), character->getXPNeeded(), character->getCurrentXP() * 100 / character->getXPNeeded());
                ImGui::Dummy(ImVec2(0,10));

                ImGui::Text("Class : %s", character->getStringClass().c_str());
                ImGui::Dummy(ImVec2(0,20));
                ImGui::Text("Description : %s", character->getDescriptions().c_str());
                ImGui::Dummy(ImVec2(0,20));

                ImGui::Text("Statistics");
                ImVec2 p_min = ImGui::GetItemRectMin();
                ImVec2 p_max = ImGui::GetItemRectMax();
                ImGui::GetWindowDrawList()->AddLine(ImVec2(p_min.x, p_max.y - 1),ImVec2(p_max.x, p_max.y - 1),IM_COL32(255, 255, 255, 255),1.0f );

                ImGui::Dummy(ImVec2(0,10));
                ImGui::Text("Health Point : %.0f", character->getMaxHealth());
                ImGui::Dummy(ImVec2(0,5));
                ImGui::Text("Attack Damage : %.0f", character->getMaxAttackDamage());
                ImGui::Dummy(ImVec2(0,5));
                ImGui::Text("Magic Damage : %.0f", character->getMaxAttackPower());
                ImGui::Dummy(ImVec2(0,5));
                ImGui::Text("Armor : %.2f", character->getMaxArmor());
                ImGui::Dummy(ImVec2(0,5));
                ImGui::Text("Magic Resistance : %.2f", character->getMaxPowerResist());
                ImGui::Dummy(ImVec2(0,5));
                ImGui::Text("Speed : %.1f", character->getCurrentSpeed());
                ImGui::Dummy(ImVec2(0,20));

                ImGui::BeginDisabled(gameplay->isInTeam(character) or gameplay->teamIsComplete());
                if (ImGui::Button("Select")) {
                    gameplay->addToTeam(character);
                }
               ImGui::EndDisabled();

                ImGui::BeginDisabled(!gameplay->isInTeam(character));
                if (ImGui::Button("UnSelect")) {
                    gameplay->removeFromTeam(character);
                }
                ImGui::EndDisabled();
            }
            else {
                ImGui::Text("Select a character...");
            }

            ImGui::EndChild();
            ImGui::Columns(1);
            ImGui::End();
            break;
        }
        case EGameState::Run :
            if (gameplay->teamIsComplete() && !runStarted) {
                intiRun();
            }
            runStarted = true;
            if (!runStarted) {
                gameplay->setRunState(EGameRunState::STARTRUN);
                runStarted = true;
            }
            gameplay->gameloop();
            if (gameplay->getRunEnded()) {
                gameState = EGameState::Menu;
                gameplay->setRunEnded(false);
                runStarted = false;
            }
            break;

        case EGameState::End :
            break;

        default:
            break;
    }

}

void Game::intiRun() {
    std::vector<Termina::Actor*> gameEntity;

    for (auto& character : gameplay->getActiveCharacters()) {
        auto it = characterPrefabMap.find(character->getName());
        if (it != characterPrefabMap.end()) {

            auto entityActor = Instantiate(it->second);
            entityActor->SetName(character->getName().c_str());
            gameEntity.push_back(entityActor);
            for (auto& child : GetChildren()) {
                std::string name = child->GetName();
                if (name.find("Slot") != std::string::npos) {
                    size_t pos = name.find("Slot ");
                    int slotIndex = std::stoi(name.substr(pos + 5)) - 1;
                    if (slotIndex >= 0 && slotIndex < gameEntity.size()) {
                        auto entity = gameEntity[slotIndex];
                        glm::vec3 slotPos = child->GetComponent<Termina::Transform>().GetPosition();
                        entity->GetComponent<Termina::Transform>().SetPosition(glm::vec3(slotPos.x,entity->GetComponent<Termina::Transform>().GetPosition().y, slotPos.z));
                    }
                }
            }

        }
    }
    for (auto& ennemi : gameplay->getEnemyVector()) {
        std::cout << ennemi->getName().c_str() << std::endl;
    }
}
