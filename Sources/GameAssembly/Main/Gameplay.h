#pragma once

#include <vector>
#include <memory>
#include "../Entities/Characters/Character.h"
#include "../Entities/Enemies/EnemyManager.h"


class Gameplay {
private:
    std::vector<std::unique_ptr<Character>> activeCharacters;

public:
    void StartTurn();
    void EndTurn();

    void StartGame();
    void EndGame();
};

