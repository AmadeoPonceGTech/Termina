#pragma once
#include "../Artefact.h"

class BearSSalmon : public Artefact
{
public:
    BearSSalmon();

    void ActingArtefact(Entity& target) override;
    void onInflictedDamage(Entity& target) override;
    void ActingArtefactEveryTurns(Entity &target) override;
};