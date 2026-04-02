#pragma once
#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include <functional>

#include <Termina/Scripting/API/ScriptingAPI.hpp>
#include "ImGui/imgui.h"
#include "ImGui/ImGuizmo.h"
#include "ImGui/imgui_internal.h"

#pragma region Gameplayincludes
#include "Entities/Characters/Range DPS/Brutus.h"
#include "Main/Gameplay/Gameplay.h"
#pragma endregion Gameplayincludes

namespace Termina {
    class Actor;
}

using namespace TerminaScript;

enum class EGameState {
    Title,
    Menu,
    Run,
    End
};


class Game : public TerminaScript::ScriptableComponent
{
public:
    Game() = default;
    Game(Termina::Actor* owner) : TerminaScript::ScriptableComponent(owner) {}

    void Start()  override;
    void Update(float deltaTime) override;

private :
    std::unique_ptr<Gameplay> gameplay;
    EGameState gameState;

    std::vector<std::shared_ptr<Character>> allCharacters;
    std::unordered_map<std::string, std::function<void(Termina::Actor*)>> componentRegistry;

    int selectedCharacter = -1;
    bool showCharacterPanel = true;

    bool runStarted = false;
};