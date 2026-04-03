#include "Artefact.h"

Artefact::Artefact() {
}

std::string Artefact::getName() { return name; }
std::string Artefact::getDescription() { return description; }
std::string Artefact::getDroppedBy() { return droppedBy; }
int Artefact::getLevel() { return level; }

void Artefact::setLevel(int _level) { this->level = _level; }
