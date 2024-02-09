#ifndef ENEMYMANAGER_H_
#define ENEMYMANAGER_H_

class EnemyManager //Top level Enemy Interface
{
    private:
        Player* tPlayer;
        EnemyBulletFactory tBullets;
        EnemyFactory tEnemies;
        EnemyWaveSpawnerFactory tWaveSpawners;
        EnemySpawnerFactory tSpawners;
    public:
        static void giveScreenArgs(int w, int h);
        EnemyManager(Player* p);
        void think(float deltaTicks, int& score);
        void draw(sf::RenderWindow& screen);
        void addEnemy(Enemy* base);
        void reset();
        EnemyFactory& GetEnemyFactory() {return tEnemies;}
        bool isEmpty() {return tSpawners.isEmpty() && tEnemies.isEmpty();}
        template <class T> void addWave(Enemy* base, float delay, int amount, float interval = 0.0f);
        template <class T> void addAlternatingWave(Enemy* base, float delay, int amount, float interval = 0.0f);
        template <class T> void addWave(Enemy* base, int Amount, float Interval);
};

template <class T> void EnemyManager::addWave(Enemy* base, float delay, int amount, float interval )
{
    tSpawners.addWave<T>(base, delay, interval, amount);
}

template <class T> void EnemyManager::addAlternatingWave(Enemy* base, float delay, int amount, float interval)
{
    tSpawners.addAlternatingWave<T>(base, delay, interval, amount);
}

template <class T> void EnemyManager::addWave(Enemy* base, int Amount, float Interval)
{
    tWaveSpawners.addWave<T>(base, Interval, Amount);
}

#endif // ENEMYMANAGER_H_
