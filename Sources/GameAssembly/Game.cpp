#include "Game.h"


#include <iostream>
#include <ostream>

#include "../Termina/Renderer/Components/CameraComponent.hpp"
#include "../Termina/Renderer/Components/MeshComponent.hpp"

void Game::Start()
{
    if (!gameplay) {
        gameplay = std::make_unique<Gameplay>();
    }



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
        for (auto& child : GetChildren())
        {
            if (child->HasComponent<Termina::CameraComponent>() && child->GetName() == "first")
            {
                // child->GetComponent<Termina::CameraComponent>().SetPrimary(true);
                std::cout << child->GetName() << std::endl;

            }
            else
                std::cout << child->GetName() << std::endl;
                // child->GetComponent<Termina::CameraComponent>().SetPrimary(false);
        }

            break;
        case GameMenu :
            break;
        case GameCharacterStats :
            break;

        default:
            break;
    }

}
