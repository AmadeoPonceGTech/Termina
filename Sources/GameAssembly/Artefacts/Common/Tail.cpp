#include "Tail.h"

Tail::Tail() {
    name = "Tail";
    description = "Heal 1% / artefact's level of max HP every turn.";
    quality = Quality::COMMON;
}

void Tail::ActingArtefact(Entity& target) {
}

void Tail::onInflictedDamage(Entity& target) {
}

void Tail::ActingArtefactEveryTurns(Entity& target) {
    target.setCurrentHealth(target.getCurrentHealth() + target.getMaxHealth() * (1.0f * level) / 100.0f);
}