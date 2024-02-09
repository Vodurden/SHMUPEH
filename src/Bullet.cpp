#include "Bullet.h"

Bullet::Bullet(Animation* anim, float Damage, float X, float Y, float W, float H, float XVel, float YVel)
{
    sprite = anim;
    sprite->start();
    x = X;
    y = Y;
    sprite->setCenter(sprite->getW() / 2, sprite->getH() / 2);

    box.Left = X;
    box.Top = Y;
    box.Right = X + 5;
    box.Bottom = Y + 5;

    w = sprite->getW();
    h = sprite->getH();
    damage = Damage;

    xVel = XVel;
    yVel = YVel;
}

Bullet::~Bullet()
{
    delete sprite;
}


void Bullet::think(float deltaTicks)
{
    float offsetX = xVel * deltaTicks;
    float offsetY = yVel * deltaTicks;
    box.Offset(offsetX, offsetY);
    x += offsetX;
    y += offsetY;
    sprite->think();
}

void Bullet::draw(sf::RenderWindow& game)
{
    sprite->draw(x, y, game);
}

void Bullet::setScale(float xfac, float yfac)
{
    sprite->setScale(xfac, yfac);
    float X = box.Left;
    float Y = box.Top;
    box = sprite->getClip();
    box.Right *= xfac;
    box.Bottom *= yfac;
    box.Offset(X, Y);
    x += X;
    y += Y;
}
