#ifndef ENEMYSPAWNER_H_
#define ENEMYSPAWNER_H_

#include <vector>
#include "EnemyWaveSpawnerFactory.h"
#include "Enemy.h"

struct SpawnData
{
    SpawnData(Enemy* b, float spawnAt, float spawnInterval, int spawnAmount) :
        spawnIn(spawnAt), spawnInterv(spawnInterval), spawnAmnt(spawnAmount) {base = b;}

    Enemy* base;
    sf::Clock spawnTimer;
    float spawnIn;
    float spawnInterv;
    int spawnAmnt;
};

//Allows you to spawn X amount of enemies every Y milliseconds after Z delay.
class EnemySpawnerBase
{
    protected:
        EnemyWaveSpawnerFactory* tWaves;
        std::vector<SpawnData*> dataStack;
        bool alternating;
    public:
        EnemySpawnerBase(EnemyWaveSpawnerFactory* wFac, Enemy* tEnm, float spawnIn, float spawnInterval, int spawnAmount, bool alt = false);
        virtual ~EnemySpawnerBase();
        bool isDone() {return dataStack.empty();}
        virtual void think() = 0;
};

template <class T> class EnemySpawner : public EnemySpawnerBase
{
    public:
        EnemySpawner(EnemyWaveSpawnerFactory* wFac, Enemy* tEnm, float spawnIn, float spawnInterval, int spawnAmount, bool alt = false) : EnemySpawnerBase(wFac, tEnm, spawnIn, spawnInterval, spawnAmount, alt) {}
        void think();
};


#endif // ENEMYSPAWNER_H_
