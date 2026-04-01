#pragma once
#include "../Artefact.h"

class CasperSEncyclopedia : public Artefact
{
public:
    CasperSEncyclopedia();

    void ActingArtefact(Entity& target) override;
    void onInflictedDamage(Entity& target) override;
    void ActingArtefactEveryTurns(Entity &target) override;
};