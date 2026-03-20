//
// Created by lmarcucci on 18/03/2026.
//

#include "EnemyManager.h"
#include <algorithm>
#include <memory>

EnemyManager::EnemyManager() {}

void EnemyManager::clearEnemies() { enemies.clear(); }
void EnemyManager::deleteEnemy(Enemy& enemy) {
    enemies.erase(
        std::remove_if(
            enemies.begin(),
            enemies.end(),
            [&enemy](const std::unique_ptr<Enemy>& e) {
                return e.get() == &enemy;
            }
        ),
        enemies.end()
    );
}

const std::vector<std::unique_ptr<Enemy>>& EnemyManager::getEnemies() const { return enemies; }