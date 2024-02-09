#include "EnemyManager.h"

EnemyManager::EnemyManager(Player* p) :
    tWaveSpawners(&tEnemies), tSpawners(&tWaveSpawners)
{
    tPlayer = p;
}

void EnemyManager::think(float deltaTicks, int& score)
{
    tBullets.think(deltaTicks, *tPlayer);
    tEnemies.think(deltaTicks, tBullets, score);
    tWaveSpawners.think();
    tSpawners.think();
}

void EnemyManager::draw(sf::RenderWindow& screen)
{
    tBullets.draw(screen);
    tEnemies.draw(screen);
}

void EnemyManager::addEnemy(Enemy* base)
{
    tEnemies.addEnemy(base);
}
void EnemyManager::giveScreenArgs(int w, int h)
{
    Enemy::giveScreenArgs(w, h);
    EnemyBulletFactory::giveScreenArgs(w, h);
    EnemyFactory::giveScreenArgs(w, h);
}

void EnemyManager::reset()
{
    tBullets.reset();
    tEnemies.reset();
    tWaveSpawners.reset();
    tSpawners.reset();
}
