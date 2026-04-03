#include "Enemy.h"

Enemy::Enemy() {
    maxLevel = 9999;

    CD1 = 0;
    CD2 = 0;
    CD3 = 0;
    CD4 = 0;

    enemyState = EnemyState::STARTTURN;
}

float Enemy::getCurrentExpDrop() const { return currentExpDrop; }
