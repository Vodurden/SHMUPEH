#ifndef ENEMYWAVESPAWNER_H_
#define ENEMYWAVESPAWNER_H_

#include "Enemy.h"
#include "EnemyFactory.h"

class EnemyWaveSpawnerBase
{
    protected:
        Enemy* base;
        EnemyFactory* enemyFactory;
        float spawnInterval; // Interval in seconds between enemy spawns
        int spawnAmount; // Max amount of enemies spawned by this spawner
        int currentAmount; // Current amount of enemies spawned by this spawner
        bool started; // Yes if the wave has started spawning
        sf::Clock spawnTimer;
    public:
        EnemyWaveSpawnerBase(Enemy* base, EnemyFactory* enemyFactory, float spawnInterval, int spawnAmount);
        virtual void think() = 0;
        bool isDone() { return currentAmount >= spawnAmount; };
};

template <class T> class EnemyWaveSpawner : public EnemyWaveSpawnerBase
{
    public:
        EnemyWaveSpawner(Enemy* base, EnemyFactory* enemyFactory, float spawnInterval, int spawnAmount) : EnemyWaveSpawnerBase(base, enemyFactory, spawnInterval, spawnAmount) {}
        void think();
};

template <class T> void EnemyWaveSpawner<T>::think()
{
    // TODO
}

#endif // ENEMYWAVESPAWNER_H_
