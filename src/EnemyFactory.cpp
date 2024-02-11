#include "EnemyFactory.h"

int EnemyFactory::gameW = 0;
int EnemyFactory::gameH = 0;

EnemyFactory::EnemyFactory()
{
    tEnemies.reserve(15);
    enemyCount = 0;
}

EnemyFactory::~EnemyFactory()
{
    tEnemies.clear();
}

void EnemyFactory::reset()
{
    tEnemies.clear();
    enemyCount = 0;
}

void EnemyFactory::think(float deltaTicks, EnemyBulletFactory& tBullets, int& score)
{
    for(std::vector<Enemy*>::iterator mIter = tEnemies.begin(); mIter != tEnemies.end();)
    {
        (*mIter)->reqThink(deltaTicks);
        (*mIter)->think(tBullets);

        if( (*mIter)->getHealth() <= 0) //Delete when the enemy is dead
        {
            score += (*mIter)->getScore();
            //tRender->addDelayText( ConvertToString( (*mIter)->getPoints() ), (*mIter)->getX(), (*mIter)->getY(), 500);

            //Explosion Animation
            Animation* tempAnim = new Animation(*(*mIter)->getExplosion());
            tempAnim->start();
            //tempAnim->setScale( (*mIter)->getScale().x * 2, (*mIter)->getScale().y * 2 );
            float scaleX = 2, scaleY = 2;
            float ratioX = (*mIter)->getW() / tempAnim->getW();
            float ratioY = (*mIter)->getH() / tempAnim->getH();
            tempAnim->setScale( (scaleX * ratioX * (*mIter)->getScale().x), (scaleY * ratioY * (*mIter)->getScale().x) );
            explosionArray.push_back(new ExplosionData(tempAnim, (*mIter)->getX(), (*mIter)->getY()));
            mIter = tEnemies.erase(mIter);
            enemyCount--;
        }
        else if( ((*mIter)->getX() < -100 || (*mIter)->getX() > gameW + 100) && !(*mIter)->isBoss()) //Delete if the enemy is outside of the screen
        {
            mIter = tEnemies.erase(mIter);
            enemyCount--;
        }
        else if( ((*mIter)->getY() < -100 || (*mIter)->getY() > gameH + 100) && !(*mIter)->isBoss())
        {
            mIter = tEnemies.erase(mIter);
            enemyCount--;
        }
        else
        {
            mIter++;
        }
    }

    for(std::vector<ExplosionData*>::iterator aIter = explosionArray.begin(); aIter != explosionArray.end();)
    {
        (*aIter)->explosion->think();
        if((*aIter)->explosion->isDone() == true)
        {
            aIter = explosionArray.erase(aIter);
        }
        else
        {
            aIter++;
        }
    }
}

void EnemyFactory::addEnemy(Enemy* base)
{
    tEnemies.push_back(base);
    enemyCount++;
}

void EnemyFactory::draw(sf::RenderWindow& game)
{
    for(std::vector<Enemy*>::iterator mIter = tEnemies.begin(); mIter != tEnemies.end(); mIter++)
    {
        (*mIter)->draw(game);
    }

    for(std::vector<ExplosionData*>::iterator aIter = explosionArray.begin(); aIter != explosionArray.end(); aIter++)
    {
        (*aIter)->explosion->draw((*aIter)->x, (*aIter)->y, game);
    }
}
