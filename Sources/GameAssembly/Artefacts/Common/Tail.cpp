#include "Tail.h"

Tail::Tail() {
    name = "Tail";
    description = "Heal 1% of max HP every turn.";
}

void Tail::ActingArtefact(Entity& target) {
}

void Tail::onInflictedDamage(Entity& target) {
}

void Tail::ActingArtefactEveryTurns(Entity& target) {
    target.setCurrentHealth(target.getCurrentHealth() + target.getMaxHealth() * level / 100.0f);
}