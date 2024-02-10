#ifndef ENEMYFACTORY_H_
#define ENEMYFACTORY_H_

#include "Enemy.h"
#include "EnemyBulletFactory.h"

struct ExplosionData
{
    ExplosionData(Animation* ep, float X, float Y)
    {
        explosion = ep;
        x = X;
        y = Y;
    }
    Animation* explosion;
    float x, y;
};
//Handles spawning and updating all onscreen enemies.
class EnemyFactory
{
    private:
        static int gameW, gameH;

        std::vector<Enemy*> tEnemies;
        std::vector<ExplosionData*> explosionArray;
        int enemyCount;
    public:
        EnemyFactory();
        ~EnemyFactory();
        static void giveScreenArgs(int w, int h) {gameW = w; gameH = h;}

        void addEnemy(Enemy* base);
        void reset();
        void think(float deltaTicks, EnemyBulletFactory& tBullets, int& score);
        void draw(sf::RenderWindow& game);
        bool isEmpty() {return tEnemies.empty();}

        const int* const getEnemyCount() {return &enemyCount;}
        std::vector<Enemy*>& getEnemies() {return tEnemies;}
};

#endif // ENEMYFACTORY_H_
