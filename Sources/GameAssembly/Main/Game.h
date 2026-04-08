#pragma once
#include <memory>
#include <vector>
#include <string>
#include <Termina/Scripting/API/ScriptingAPI.hpp>
#include "../../ThirdParty/ImGui/imgui.h"
#include "../../ThirdParty/ImGui/imgui_internal.h"

#pragma region Gameplayincludes
#include "../Entities/Characters/Range DPS/Brutus.h"
#include "Gameplay/Gameplay.h"
#pragma endregion Gameplayincludes

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
    int selectedCharacter = -1;
    bool showCharacterPanel = true;

    bool runStarted = false;
};