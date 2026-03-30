#pragma once
#include "../Artefact.h"

class KnightSBadge : public Artefact
{
public:
    KnightSBadge();

    void ActingArtefact(Entity& target) override;
    void onInflictedDamage(Entity& target) override;
    void ActingArtefactEveryTurns(Entity &target) override;
};