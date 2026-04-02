#pragma once
#include "../Artefact.h"

class RattataSkull : public Artefact
{
public:
    RattataSkull();

    void ActingArtefact(Entity& target) override;
    void onInflictedDamage(Entity& target) override;
    void ActingArtefactEveryTurns(Entity &target) override;
};