#include "Game.h"

#include <iostream>
#include <ostream>

#include "../../Termina/Renderer/Components/CameraComponent.hpp"
#include "../../Termina/Renderer/Components/MeshComponent.hpp"

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

    allCharacters.emplace_back(std::make_shared<Diane>());
    allCharacters.emplace_back(std::make_shared<Emilie>());
    allCharacters.emplace_back(std::make_shared<Claire>());
    allCharacters.emplace_back(std::make_shared<Marcus>());
    allCharacters.emplace_back(std::make_shared<Brutus>());
    allCharacters.emplace_back(std::make_shared<Edward>());
    allCharacters.emplace_back(std::make_shared<Alex>());
    allCharacters.emplace_back(std::make_shared<Penelope>());

}

void Game::Update(float deltaTime)
{

    switch (gameState)
    {

        case EGameState::Title : {
            ImGui::SetNextWindowSize(ImVec2(1280, 720));
            ImGui::Begin("MainWindow");

            ImGui::Dummy(ImVec2(0,100));
            ImGui::SetWindowFontScale(5.f);
            std::string title = "ENDLESS ROGUE";
            float textWidth = ImGui::CalcTextSize(title.c_str()).x;
            float avail = ImGui::GetContentRegionAvail().x;
            ImGui::SetCursorPosX((avail - textWidth) * 0.5f);
            ImGui::Text("ENDLESS ROGUE");

            ImGui::Dummy(ImVec2(0,250));

            float buttonWidth = 120.0f;
            ImGui::SetCursorPosX((avail - buttonWidth) * 0.5f);
            if (ImGui::Button("Play")) { gameState = EGameState::Menu; }

            ImGui::End();
            }
            break;

        case EGameState::Menu :
        {
            ImGui::SetNextWindowSize(ImVec2(1280, 720));
            ImGui::Begin("MainWindow");

            ImGui::SetWindowFontScale(1.f);

            ImGui::Text("Select your characters");
            ImGui::SameLine();
            ImGui::BeginDisabled(!gameplay->TeamIsComplete());
            if (ImGui::Button("Launch Run")) {
                gameState = EGameState::Run;
            };
            ImGui::EndDisabled();

            // ===== LAYOUT SIMPLE =====
            ImGui::Columns(2, nullptr, true);
            // ===== LEFT: LIST =====
            ImGui::BeginChild("CharacterList", ImVec2(200, 0), true);
            for (int i = 0; i < allCharacters.size(); i++) {
                if (ImGui::Selectable(allCharacters[i]->getName().c_str(), selectedCharacter == i)) {
                    selectedCharacter = i;
                }
            }

            ImGui::Dummy(ImVec2(0,305));

            ImGui::Text("Character Selected :");

            ImGui::Dummy(ImVec2(0,10));

            for (int i = 0; i < gameplay->getActiveCharacters().size(); i++) {
                ImGui::Text("%s", gameplay->getActiveCharacters()[i]->getName().c_str());
            }

            ImGui::EndChild();
            ImGui::NextColumn();

            // ===== RIGHT: DETAILS =====
            ImGui::BeginChild("CharacterDetails", ImVec2(-1, 0), true);

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

                ImGui::BeginDisabled(gameplay->IsInTeam(character) or gameplay->TeamIsComplete());
                if (ImGui::Button("Select")) {
                    gameplay->AddToTeam(character);
                }
               ImGui::EndDisabled();

                ImGui::BeginDisabled(!gameplay->IsInTeam(character));
                if (ImGui::Button("UnSelect")) {
                    gameplay->RemoveFromTeam(character);
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
            if (!runStarted) {
                gameplay->setRunState(EGameRunState::STARTRUN);
                runStarted = true;
            }
            gameplay->Gameloop();
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
