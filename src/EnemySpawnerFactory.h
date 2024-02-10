#ifndef ENEMYSPAWNERFACTORY_H_
#define ENEMYSPAWNERFACTORY_H_

#include "EnemySpawner.h"
#include "EnemyWaveSpawnerFactory.h"

//Allows you to spawn EnemyWaveSpawners
class EnemySpawnerFactory
{
    private:
        EnemyWaveSpawnerFactory* wFac;
        std::vector<EnemySpawnerBase*> tSpawners;
    public:
        EnemySpawnerFactory(EnemyWaveSpawnerFactory* w) {wFac = w;}
        ~EnemySpawnerFactory();
        template<class T> void addWave(Enemy* enm, float delay, float interval, int amount);
        void think();
        void reset();
        bool isEmpty() {return tSpawners.empty();}
};

template <class T> void EnemySpawnerFactory::addWave(Enemy* enm, float delay, float interval, int amount)
{
    tSpawners.push_back(new EnemySpawner<T>(wFac, enm, delay, interval, amount));
}

#endif // ENEMYSPAWNERFACTORY_H_
