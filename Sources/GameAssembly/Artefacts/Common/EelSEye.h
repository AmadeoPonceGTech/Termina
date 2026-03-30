#pragma once
#include "../Artefact.h"

class EelSEye : public Artefact
{
public:
    EelSEye();

    void ActingArtefact(Entity& target) override;
    void onInflictedDamage(Entity& target) override;
    void ActingArtefactEveryTurns(Entity &target) override;
};