#include "EnemySpawnerFactory.h"

template <class T> void EnemySpawnerFactory::addWave(Enemy* enm, float delay, float interval, int amount)
{
    tSpawners.push_back(new EnemySpawner<T>(wFac, enm, delay, interval, amount));
}

EnemySpawnerFactory::~EnemySpawnerFactory()
{
    for(std::vector<EnemySpawnerBase*>::iterator mIter = tSpawners.begin(); mIter != tSpawners.end(); mIter++)
    {
        delete (*mIter);
    }

    tSpawners.clear();
}

void EnemySpawnerFactory::reset()
{
    for(std::vector<EnemySpawnerBase*>::iterator mIter = tSpawners.begin(); mIter != tSpawners.end(); mIter++)
    {
        delete (*mIter);
    }

    tSpawners.clear();
}

void EnemySpawnerFactory::think()
{
    for(std::vector<EnemySpawnerBase*>::iterator mIter = tSpawners.begin(); mIter != tSpawners.end(); mIter++)
    {
        (*mIter)->think();
    }

    for(std::vector<EnemySpawnerBase*>::iterator mIter = tSpawners.begin(); mIter != tSpawners.end();)
    {
        if( (*mIter)->isDone() == true)
            mIter = tSpawners.erase(mIter);
        else
            mIter++;
    }
}
