#include "EnemySpawner.h"

EnemySpawnerBase::EnemySpawnerBase(EnemyWaveSpawnerFactory* wFac, Enemy* tEnm, float spawnIn, float spawnInterval, int spawnAmount, bool alt)
{
    tWaves = wFac;
    dataStack.push_back(new SpawnData(tEnm, spawnIn, spawnInterval, spawnAmount));
    alternating = alt;
}
EnemySpawnerBase::~EnemySpawnerBase()
{
    for(std::vector<SpawnData*>::iterator mIter = dataStack.begin(); mIter != dataStack.end(); mIter++)
    {
        delete (*mIter);
    }
}
