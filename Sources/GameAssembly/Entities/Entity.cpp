
#include "Entity.h"

Entity::Entity()
{
    CD1 = 0;
    CD2 = 0;
    CD3 = 0;
    CD4 = 0;
}

float Entity::getCurrentHealth() { return currentHealth; }
float Entity::getShield() { return shield; }
float Entity::getCurrentAttackDamage() { return currentAttackDamage; }
float Entity::getCurrentAttackPower() { return currentAttackPower; }
float Entity::getCurrentArmor() { return currentArmor; }
float Entity::getCurrentPowerResist() { return currentPowerResist; }

int Entity::getCD1() { return CD1; }
int Entity::getCD2() { return CD2; }
int Entity::getCD3() { return CD3; }
int Entity::getCD4() { return CD4; }



void Entity::setCurrentHealth(float newHealth) { currentHealth = newHealth; }
void Entity::setShield(float newShield) { shield = newShield; }
void Entity::setCurrentAttackDamage(float newDamage) { currentAttackDamage = newDamage; }
void Entity::setCurrentAttackPower(float newPower) { currentAttackPower = newPower; }
void Entity::setCurrentArmor(float newArmor) { currentArmor = newArmor; }
void Entity::setCurrentPowerResist(float newPowerResist) { currentPowerResist = newPowerResist; }

void Entity::setCD1(int newCD1) { CD1 = newCD1; }
void Entity::setCD2(int newCD2) { CD2 = newCD2; }
void Entity::setCD3(int newCD3) { CD3 = newCD3; }
void Entity::setCD4(int newCD4) { CD4 = newCD4; }

