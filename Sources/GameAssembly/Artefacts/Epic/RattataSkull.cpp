#include "RattataSkull.h"

RattataSkull::RattataSkull() {
    name = "Rattata skull";
    description = "Boost resources by 2 / artefact's level.";
    droppedBy = "Rat";
    quality = Quality::EPIC;
}
+
void RattataSkull::ActingArtefact(Entity& target) {
    target.resourcesWon = target.resourcesWon + 2 * level;
}

void RattataSkull::onInflictedDamage(Entity& target) {
}

void RattataSkull::ActingArtefactEveryTurns(Entity& target) {
}