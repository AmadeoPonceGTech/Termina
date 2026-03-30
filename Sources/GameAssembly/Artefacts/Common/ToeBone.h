#pragma once
#include "../Artefact.h"

class ToeBone : public Artefact
{
public:
    ToeBone();

    void ActingArtefact(Entity& target) override;
    void onInflictedDamage(Entity& target) override;
    void ActingArtefactEveryTurns(Entity &target) override;
};