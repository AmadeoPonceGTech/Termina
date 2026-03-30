#include "EelSEye.h"

EelSEye::EelSEye() {
    name = "Eel's eye";
    description = "Increase resources drop (+1 / artefact's level).";
}

void EelSEye::ActingArtefact(Entity& target) {
    target.ressourcesWon = target.ressourcesWon + level;
}

void EelSEye::onInflictedDamage(Entity& target) {
}

void EelSEye::ActingArtefactEveryTurns(Entity& target) {
}