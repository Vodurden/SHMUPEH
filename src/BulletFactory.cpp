#include "BulletFactory.h"

int BulletFactory::gameW = 0;
int BulletFactory::gameH = 0;

BulletFactory::BulletFactory()
{
    tBullets.reserve(25);
    bulletCount = 0;
    damageRender = new TextRenderer("Graphics/Consola.ttf", 16, sf::Color(255, 0, 0));
}

BulletFactory::~BulletFactory()
{
    for(std::vector<Bullet*>::iterator mIter = tBullets.begin(); mIter != tBullets.end(); mIter++)
    {
        delete (*mIter);
    }

    tBullets.clear();
}

void BulletFactory::reset()
{
    for(std::vector<Bullet*>::iterator mIter = tBullets.begin(); mIter != tBullets.end(); mIter++)
    {
        delete (*mIter);
    }

    tBullets.clear();
}

void BulletFactory::addBullet(Bullet* base)
{
    tBullets.push_back(base);
    bulletCount += 1;
}

void BulletFactory::think(float deltaTicks, std::vector<Enemy*>& enemies)
{
    bool iterates;
    bool blankBullet = false;

    damageRender->think();

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
            for(std::vector<Enemy*>::iterator eIter = enemies.begin(); eIter != enemies.end();)
            {
                    if( (*mIter)->intersects( (*eIter)->getBox() ) && !blankBullet )
                    {
                        (*eIter)->damage( (*mIter)->getDamage() );
                        iterates = false;
                        blankBullet = true;
                        bulletCount -= 1;
                        damageRender->addDelayText(std::to_string((*mIter)->getDamage()), (*mIter)->getX(), (*mIter)->getY(), 0.6f);
                    }
                    else
                    {
                        ++eIter;
                    }
            }
        }

        if(iterates)
            ++mIter;
        else
            mIter = tBullets.erase(mIter);
    }
}

void BulletFactory::draw(sf::RenderWindow& game)
{
    for(std::vector<Bullet*>::iterator mIter = tBullets.begin(); mIter != tBullets.end(); mIter++)
    {
       (*mIter)->draw(game);
    }

    damageRender->draw(game);
}
