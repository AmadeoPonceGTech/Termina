#include "RatTooth.h"

RatTooth::RatTooth() {
    name = "Bear's Foot";
    description = "Heal 2% / artefact's level health of every damage dealt.";
    droppedBy = "Bear";
    quality = Quality::COMMON;
}

void RatTooth::actingArtefact(Entity& target) {
    target.setPoisonMultiplier(1.2f * level);
}

void RatTooth::onInflictedDamage(Entity& target) {
}

void RatTooth::actingArtefactEveryTurns(Entity& target) {
}