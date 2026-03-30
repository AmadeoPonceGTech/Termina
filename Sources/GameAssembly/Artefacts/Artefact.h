#pragma once
#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>
#include <random>
#include <memory>
#include "../Entities/Characters/Character.h"

class Artefact
{
protected:
    std::string name;
    std::string description;
    int level = 1;

public:
    virtual ~Artefact() = default;
    Artefact();

    virtual void ActingArtefact(Entity& target) = 0;
    virtual void onInflictedDamage(Entity& target) = 0;
    virtual void ActingArtefactEveryTurns(Entity& target) = 0;

#pragma region Getters

    virtual std::string getName();
    virtual std::string getDescription();

#pragma endregion

#pragma region Setters

#pragma endregion

};