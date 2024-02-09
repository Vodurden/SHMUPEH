#include "EnemyWaveSpawnerFactory.h"

EnemyWaveSpawnerFactory::~EnemyWaveSpawnerFactory()
{
    this->reset();
}

void EnemyWaveSpawnerFactory::reset()
{
    for(std::vector<EnemyWaveSpawnerBase*>::iterator mIter = tWaves.begin(); mIter != tWaves.end(); mIter++)
    {
        delete (*mIter);
    }

    tWaves.clear();
}

void EnemyWaveSpawnerFactory::think()
{
    for(std::vector<EnemyWaveSpawnerBase*>::iterator mIter = tWaves.begin(); mIter != tWaves.end();)
    {
        (*mIter)->think();

        if( (*mIter)->isDone() )
        {
            mIter = tWaves.erase(mIter);
        }
        else
        {
            mIter++;
        }
    }
}


void EnemyWaveSpawnerFactory::addBaseWave(EnemyWaveSpawnerBase* waveSpawner)
{
    tWaves.push_back(waveSpawner);
}
