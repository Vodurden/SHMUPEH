#ifndef ENEMYWAVESPAWNERFACTORY_H_
#define ENEMYWAVESPAWNERFACTORY_H_

//Allows you to spawn X enemies every Y interval using another class.
class EnemyWaveSpawnerFactory
{
    private:
        EnemyFactory* eFact;
        std::vector<EnemyWaveSpawnerBase*> tWaves;
    public:
        EnemyWaveSpawnerFactory(EnemyFactory* eF) {eFact = eF;}
        ~EnemyWaveSpawnerFactory();
        template <class T> void addWave(Enemy* base, float Interval, int Amount);
        void addBaseWave(EnemyWaveSpawnerBase* waveSpawner);
        void reset();
        void think();
};

#endif // ENEMYWAVESPAWNERFACTORY_H_
