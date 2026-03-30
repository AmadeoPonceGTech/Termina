#pragma once
#include "../Artefact.h"

class BearSFoot : public Artefact
{
public:
    BearSFoot();

    void ActingArtefact(Entity& target) override;
    void onInflictedDamage(Entity& target) override;
    void ActingArtefactEveryTurns(Entity &target) override;
};