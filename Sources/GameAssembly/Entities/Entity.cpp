
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

float Entity::getMaxHealth() { return maxHealth; }
float Entity::getMaxAttackDamage() { return maxAttackDamage; }
float Entity::getMaxAttackPower() { return maxAttackPower; }
float Entity::getMaxArmor() { return maxArmor; }
float Entity::getMaxPowerResist() { return maxPowerResist; }

int Entity::getCD1() { return CD1; }
int Entity::getCD2() { return CD2; }
int Entity::getCD3() { return CD3; }
int Entity::getCD4() { return CD4; }

bool Entity::getFirstAbilityUp() { return firstAbilityUp; }
bool Entity::getSecondAbilityUp() { return secondAbilityUp; }
bool Entity::getThirdAbilityUp() { return thirdAbilityUp; }
bool Entity::getFourthAbilityUp() { return fourthAbilityUp; }

bool Entity::getIsPoisoned() { return isPoisoned; }
bool Entity::getIsBurned() { return isBurned; }
bool Entity::getIsTaunt() { return isTaunt; }

float Entity::getPoison() {
    switch (poison) {
        case Poison::NOT_POISONED:
            return 0.0f;
        case Poison::FIRST_TURN:
            return 15.0f;
        case Poison::SECOND_TURN:
            return 12.0f;
        case Poison::THIRD_TURN:
            return 8.0f;
        case Poison::FOURTH_TURN:
            return 5.0f;
        case Poison::FIFTH_TURN:
            return 3.0f;
        default:
            return 0.0f;
    }
}

float Entity::getBurn() {
    switch (burn) {
        case Burn::NOT_BURNED:
            return 0.0f;
        case Burn::FIRST_TURN:
            return 15.0f;
        case Burn::SECOND_TURN:
            return 12.0f;
        case Burn::THIRD_TURN:
            return 8.0f;
        default:
            return 0.0f;
    }
}

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

void Entity::setIsPoisoned(bool newIsPoisoned) { isPoisoned = newIsPoisoned; }
void Entity::setIsBurned(bool newIsBurned) { isBurned = newIsBurned; }
void Entity::setIsTaunt(bool newIsTaunt) { isTaunt = newIsTaunt; }

