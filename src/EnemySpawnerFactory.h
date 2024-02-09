#ifndef ENEMYSPAWNERFACTORY_H_
#define ENEMYSPAWNERFACTORY_H_

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

#endif // ENEMYSPAWNERFACTORY_H_
