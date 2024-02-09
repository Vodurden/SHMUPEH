#include "EnemySpawner.h"

template <class T> class EnemySpawner : public EnemySpawnerBase
{
    public:
        EnemySpawner(EnemyWaveSpawnerFactory* wFac, Enemy* tEnm, float spawnIn, float spawnInterval, int spawnAmount, bool alt = false) : EnemySpawnerBase(wFac, tEnm, spawnIn, spawnInterval, spawnAmount, alt) {}
        void think();
};

template <class T> void EnemySpawner<T>::think()
{
    for(std::vector<SpawnData*>::iterator mIter = dataStack.begin(); mIter != dataStack.end();)
    {
        if( (*mIter)->spawnTimer.GetElapsedTime() > (*mIter)->spawnIn )
        {
            tWaves->addWave<T>((*mIter)->base, (*mIter)->spawnInterv, (*mIter)->spawnAmnt);
            mIter = dataStack.erase(mIter);
        }
        else
        {
            mIter++;
        }
    }
}

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
