#ifndef ENEMYMANAGER_H_
#define ENEMYMANAGER_H_

#include "Player.h"
#include "EnemyBulletFactory.h"
#include "EnemySpawnerFactory.h"
#include "EnemyFactory.h"

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
        bool isEmpty()
        {
          return tSpawners.isEmpty() && tEnemies.isEmpty();
        }
        template <class T> void addWave(Enemy* base, float delay, int amount, float interval = 0.0f);
        template <class T> void addWave(Enemy* base, int amount, float interval);
};

template <class T> void EnemyManager::addWave(Enemy* base, float delay, int amount, float interval )
{
    tSpawners.addWave<T>(base, delay, interval, amount);
}

template <class T> void EnemyManager::addWave(Enemy* base, int amount, float interval)
{
   tWaveSpawners.addWave<T>(base, interval, amount);
}

#endif // ENEMYMANAGER_H_
