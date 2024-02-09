#include "EnemyBulletFactory.h"

int EnemyBulletFactory::gameW = 0;
int EnemyBulletFactory::gameH = 0;

EnemyBulletFactory::EnemyBulletFactory()
{
    tBullets.reserve(15);
}

EnemyBulletFactory::~EnemyBulletFactory()
{
    for(std::vector<Bullet*>::iterator mIter = tBullets.begin(); mIter != tBullets.end(); mIter++)
    {
        delete (*mIter);
    }

    tBullets.clear();
}

void EnemyBulletFactory::addBullet(Bullet* base)
{
    tBullets.push_back(base);
}

void EnemyBulletFactory::think(float deltaTicks, Player& tPlayer)
{
    bool iterates;
    bool blankBullet = false;

    for(std::vector<Bullet*>::iterator mIter = tBullets.begin(); mIter != tBullets.end();)
    {
        (*mIter)->think(deltaTicks);

        iterates = true;
        blankBullet = false;

        if( (*mIter)->getX() < -50 || (*mIter)->getX() > gameW + 50)
        {
            bulletCount -= 1;
            iterates = false;
            blankBullet = true;
        }
        else if( (*mIter)->getY() < - 50 || (*mIter)->getY() > gameH + 50 )
        {
            bulletCount -= 1;
            iterates = false;
            blankBullet = true;
        }

        if(iterates)
        {
            if( (tPlayer.intersects( (*mIter)->getBox() ) && !blankBullet) )
            //if(check_collision( (*mIter)->getBox(), tPlayer->getBox() ) && !blankBullet ) //Kill the enemy & bullet
            {
                tPlayer.damage( (*mIter)->getDamage());
                bulletCount -= 1;
                iterates = false;
                blankBullet = true;
            }
        }

        if(iterates)
            ++mIter;
        else
            mIter = tBullets.erase(mIter);
    }
}

void EnemyBulletFactory::draw(sf::RenderWindow& game)
{
    for(std::vector<Bullet*>::iterator mIter = tBullets.begin(); mIter != tBullets.end(); mIter++)
    {
        (*mIter)->draw(game);
    }
}
