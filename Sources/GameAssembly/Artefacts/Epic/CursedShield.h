#pragma once
#include "../Artefact.h"

class CursedShield : public Artefact
{
public:
    CursedShield();

    void ActingArtefact(Entity& target) override;
    void onInflictedDamage(Entity& target) override;
    void ActingArtefactEveryTurns(Entity &target) override;
};