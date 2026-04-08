#pragma once
#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include <functional>

#include <Termina/Scripting/API/ScriptingAPI.hpp>
#include "../../ThirdParty/ImGui/imgui.h"
#include "../../ThirdParty/ImGui/imgui_internal.h"

#pragma region Gameplayincludes
#include "../Termina/Scripting/API/ScriptableComponent.hpp"
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

    void intiRun();

private :
    std::unique_ptr<Gameplay> gameplay;
    EGameState gameState;

    std::vector<std::shared_ptr<Character>> allCharacters;

    int selectedCharacter = -1;
    bool showCharacterPanel = true;

    bool runStarted = false;

    TerminaScript::Prefab p_Diane;
    TerminaScript::Prefab p_Emilie;
    TerminaScript::Prefab p_Claire;
    TerminaScript::Prefab p_Marcus;
    TerminaScript::Prefab p_Brutus;
    TerminaScript::Prefab p_Edward;
    TerminaScript::Prefab p_Alex;
    TerminaScript::Prefab p_Penelope;

    std::unordered_map<std::string, TerminaScript::Prefab> characterPrefabMap;

};