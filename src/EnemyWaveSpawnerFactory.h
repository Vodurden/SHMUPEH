#ifndef ENEMYWAVESPAWNERFACTORY_H_
#define ENEMYWAVESPAWNERFACTORY_H_

#include "EnemyFactory.h"
#include "EnemyWaveSpawner.h"

//Allows you to spawn X enemies every Y interval using another class.
class EnemyWaveSpawnerFactory
{
    private:
        EnemyFactory* eFact;
        std::vector<EnemyWaveSpawnerBase*> tWaves;
    public:
        EnemyWaveSpawnerFactory(EnemyFactory* eF) {eFact = eF;}
        ~EnemyWaveSpawnerFactory();
        template <class T> void addWave(Enemy* base, float interval, int amount);
        void addBaseWave(EnemyWaveSpawnerBase* waveSpawner);
        void reset();
        void think();
};

template <class T> void EnemyWaveSpawnerFactory::addWave(Enemy* base, float interval, int amount)
{
    tWaves.push_back(new EnemyWaveSpawner<T>(base, eFact, interval, amount));
}

#endif // ENEMYWAVESPAWNERFACTORY_H_
