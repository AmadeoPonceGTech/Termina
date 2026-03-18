#include "Game.h"


#include <iostream>
#include <ostream>

void Game::Start()
{
}

void Game::Update(float deltaTime)
{
    bool show = true;
    ImGui::SetNextWindowSize(ImVec2(500, 500));
    ImGui::Begin("ImGui Menu", &show);
    ImGui::RadioButton("radio a",(int*)&gameState, GameRun); ImGui::SameLine();
    ImGui::RadioButton("radio b", (int*)&gameState, GameMenu); ImGui::SameLine();
    ImGui::RadioButton("radio c", (int*)&gameState, GameCharacterStats);
    ImGui::End();

    switch (gameState) {

        case GameRun :
            std::cout << "Game Run" << std::endl;
            break;
        case GameMenu :
            std::cout << "Game Menu" << std::endl;
            break;
        case GameCharacterStats :
            std::cout << "Game Character Stats" << std::endl;
            break;

        default:
            break;
    }

}
