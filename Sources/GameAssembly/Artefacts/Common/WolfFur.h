#pragma once
#include "../Artefact.h"

class WolfFur : public Artefact
{
public:
    WolfFur();

    void ActingArtefact(Entity& target) override;
    void onInflictedDamage(Entity& target) override;
    void ActingArtefactEveryTurns(Entity &target) override;
};