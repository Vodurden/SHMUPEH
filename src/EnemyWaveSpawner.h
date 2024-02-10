#ifndef ENEMYWAVESPAWNER_H_
#define ENEMYWAVESPAWNER_H_

#include "Enemy.h"
#include "EnemyFactory.h"

class EnemyWaveSpawnerBase
{
    protected:
        Enemy* base;
        EnemyFactory* enemyFactory;
        int amount; // Max amount of enemies spawned by this spawner
        int currentAmount; // Current amount of enemies spawned by this spawner
        float spawnInterval; // Interval in seconds between enemy spawns
        bool started; // Yes if the wave has started spawning
        sf::Clock spawnTimer;
    public:
        void think();
        bool isDone();
};


#endif // ENEMYWAVESPAWNER_H_
