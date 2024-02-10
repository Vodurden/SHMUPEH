#include "EnemySpawnerFactory.h"

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
