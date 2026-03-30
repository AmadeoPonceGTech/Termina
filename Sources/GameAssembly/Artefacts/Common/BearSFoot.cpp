#include "BearSFoot.h"

BearSFoot::BearSFoot() {
    name = "Bear's Foot";
    description = "Heal 2% health of every damage dealt.";
}

void BearSFoot::ActingArtefact(Entity& target) {
}

void BearSFoot::onInflictedDamage(Entity& target) {
    target.setCurrentHealth(target.getCurrentHealth() + target.getMaxHealth() * (2.0f * level) / 100.0f);
}

void BearSFoot::ActingArtefactEveryTurns(Entity& target) {
}