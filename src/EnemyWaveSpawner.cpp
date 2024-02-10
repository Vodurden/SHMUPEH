#include "EnemyWaveSpawner.h"

EnemyWaveSpawnerBase::EnemyWaveSpawnerBase(Enemy* base, EnemyFactory* enemyFactory, float spawnInterval, int spawnAmount) {
    this->base = base;
    this->enemyFactory = enemyFactory;
    this->spawnInterval = spawnInterval;
    this->spawnAmount = spawnAmount;
    this->currentAmount = 0;
    this->started = false;
}


EnemyWaveSpawnerBase::~EnemyWaveSpawnerBase() {
    delete base;
}
