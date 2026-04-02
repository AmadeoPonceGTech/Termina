#include "CasperSEncyclopedia.h"

CasperSEncyclopedia::CasperSEncyclopedia() {
    name = "Casper's encyclopedia";
    description = "Increase by 0.5% / artefact's level the AP every turns.";
    droppedBy = "Ghost";
    quality = Quality::EPIC;
}

void CasperSEncyclopedia::ActingArtefact(Entity& target) {
}

void CasperSEncyclopedia::onInflictedDamage(Entity& target) {
}

void CasperSEncyclopedia::ActingArtefactEveryTurns(Entity& target) {
    target.setCurrentAttackPower(target.getCurrentAttackPower() * 1.0f + (3.0f * level) / 100.0f);
}