#pragma once
#include "../Artefact.h"

class Tail : public Artefact
{
public:
    Tail();

    void ActingArtefact(Entity& target) override;
    void onInflictedDamage(Entity& target) override;
    void ActingArtefactEveryTurns(Entity &target) override;
};