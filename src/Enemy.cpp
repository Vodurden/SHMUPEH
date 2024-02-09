#include "Enemy.h"

int Enemy::screenW = 0;
int Enemy::screenH = 0;

void Enemy::setSprite(Animation* Sprite)
{
    if(sprite ==  0)
    {
        sprite = Sprite;
    }
    else
    {
        Logger::log("Enemy::setSprite() has been called on a sprite that is not NULL", LOGTYPE_ERROR);
        sprite = Sprite;
    }
}

Enemy::Enemy(bool rev)
{
    sprite = 0;
    explosion = ResourceManager::getAnimation("Explosion");
    xVel = 0;
    yVel = 0;
    points = 0;
    speed = 0;
    reverse = rev;
}

void Enemy::offset(float x, float y)
{
    /*float oX = x;
    float oY = y;
    if(box.Right + oX > screenW)
        oX -= box.Right - screenW;
    else if(box.Left < 0)
        oX += fabs(box.Left);

    if(box.Top < 0)
        oY += fabs(box.Top);
    else if(box.Bottom + oY > screenH)
        oY -= box.Bottom - screenH;*/

    box.Offset(x, y);
}

Enemy::Enemy(const Enemy& rhs)
{
    sprite = new Animation(*(rhs.sprite));
    explosion = new Animation(*(rhs.explosion));
    explosion->setScale(rhs.explosion->getScale().x, rhs.explosion->getScale().y);
    sprite->setScale(rhs.sprite->getScale().x, rhs.sprite->getScale().y);
    box = rhs.box;
    xVel = rhs.xVel;
    yVel = rhs.yVel;
    health = rhs.health;
    maxhealth = rhs.maxhealth;
    speed = rhs.speed;
    originX = rhs.originX;
    originY = rhs.originY;
    boss = rhs.boss;
    reverse = rhs.reverse;
    normColor = rhs.normColor;
    shotTimer = rhs.shotTimer;
    colTimer = rhs.colTimer;
    points = rhs.points;

    tWaypoints = rhs.tWaypoints;
}

Enemy::~Enemy()
{
    delete sprite;
}

void Enemy::calculateRect(float x, float y)
{
    if(sprite != 0)
    {
        box.Left = x;
        box.Right = box.Left + sprite->getW();
        box.Top = y;
        box.Bottom = box.Top + sprite->getH();
        normColor = sprite->getColor();
        originX = x;
        originY = y;
    }
    else
    {
        Logger::log("attempt to calculate rect on class Enemy with no sprite", LOGTYPE_ERROR);
    }
}

void Enemy::shootAtPoint(EnemyBulletFactory& tBullets, Animation* anim, int damage, float tarX, float tarY, float speed)
{
    float TarX = tarX;
    if(reverse)
        TarX = screenW - tarX;

    float x = box.Left + ((box.Right - box.Left) / 2); //Calculates the middle of the sprite (X)
    float y = box.Top + ((box.Bottom - box.Top) / 2);
    float dy = y - tarY;
    float dx = x - TarX;
    float a = atan2(dy, dx);
    float xOff = -(speed * cos(a));
    float yOff = -(speed * sin(a));
    float rotate = ((atan2(tarY - y,tarX - x) / (4.0f * atan(1.0f))) * 180) - 90;
    rotate = 360 - rotate;
    anim->rotate(rotate);
    Bullet* temp = new Bullet(anim, damage, x, y, anim->getW(), anim->getH(), xOff, yOff);
    tBullets.addBullet(temp);
}

void Enemy::reqThink(float deltaTicks)
{
    float xOff, yOff;
    if(!tWaypoints.empty()) //Waypoints override xvel
    {
        sf::Vector2f waypos = tWaypoints.getCurrentWaypoint();
        float x = box.Left + ((box.Right - box.Left) / 2);
        float y = box.Top + ((box.Bottom - box.Top) / 2);

        float dy = y - waypos.y;
        float dx = x - waypos.x;
        float a = atan2(dy, dx);
        xOff = -(speed * cos(a));
        yOff = -(speed * sin(a));
        xVel = xOff;
        yVel = yOff;

        sf::FloatRect t(waypos.x, waypos.y, waypos.x + 5, waypos.y + 5);
        if(box.Intersects(t))
        {
            tWaypoints.moveToNextWaypoint();
            if(tWaypoints.getCurrentWaypointIndex() == 4)
            {
                tWaypoints.getCurrentWaypointIndex();
            }
        }
    }
    else
    {
        xOff = xVel;
        yOff = yVel;
    }

    this->offset(xOff * deltaTicks, yOff * deltaTicks);


    if(colTimer.GetElapsedTime() > 0.1f && colTimer.GetElapsedTime() < 0.2f)
    {
        sprite->setColor(normColor);
    }
}

void Enemy::draw(sf::RenderWindow& screen)
{
    sprite->draw(box.Left, box.Top, screen);
}

void Enemy::addWaypoint(const int x, const int y)
{
    if(!reverse)
    {
        tWaypoints.addWaypoint(x, y);
    }
    else
    {
        int revX = screenW - x;
        tWaypoints.addWaypoint(revX, y);
    }
}

void Enemy::damageByPercent(float p)
{
    health -= (maxhealth * p) / 100.0f;
    if(health < 0)
        health = 0.0f;

    damageEffect();
}

void Enemy::damage(float h)
{
    health -= h;
    if(health < 0)
        health = 0;

    damageEffect();
}

void Enemy::damageEffect()
{
    sprite->setColor(sf::Color(200, 200, 200, 255));
    colTimer.Reset();
}

///|/// Wanderer ///|///
Wanderer::Wanderer(float x, float y, float WPX, float WPY, bool rev) : Enemy(rev)
{
    registerName("Wanderer");
    this->setSprite(ResourceManager::getAnimation("Insect"));
    calculateRect(x, y); //Set up how big our collision box is, based off the Animation
    boss = false; //Bosses don't die when they go out of range
    points = 20;
    speed = 150; //Pixels per Second
    health = 20;

    //Waypoints here - Waypoints loop back to the first when they reach the end
    setWPMode(WP_SINGLE);
    addWaypoint(screenW - (int)WPX, (int)WPY);
    addWaypoint(screenW - (int)WPX, screenH - (int)WPY);
    //addWaypoint((int)WPX, screenH - (int)WPY);
    //End Waypoints
}

void Wanderer::think(EnemyBulletFactory& tBullets)
{
    //Bullet Logic Here
    if(shotTimer.GetElapsedTime() > 0.4f)
    {
        Animation* anim = ResourceManager::getAnimation("EnemyRapidBullet");
        shootAtPoint(tBullets, anim, 4, screenW / 2, screenH / 2, 150);
        shotTimer.Reset();
    }
}
///|/// -------- ///|///

///|/// Runstrike ///|///
Runstrike::Runstrike(float x, float y, bool rev) : Enemy(false)
{
    registerName("Runstrike");
    Animation* tempAnim = ResourceManager::getAnimation("Purple_Fighter");
    tempAnim->setScale(0.75f, 0.75f);
    this->setSprite(tempAnim);
    calculateRect(x, y); //Set up how big our collision box is, based off the Animation
    boss = false; //Bosses don't die when they go out of range
    points = 5;
    speed = 160; //Pixels per Second
    health = 2;

    //Waypoints here - Waypoints loop back to the first when they reach the end
    setWPMode(WP_SINGLE);
    addWaypoint((int)box.Left, screenH + 500);
    //End Waypoints

    shotTimer.Reset();
}

void Runstrike::think(EnemyBulletFactory& tBullets)
{
    //Bullet Logic Here
    if(shotTimer.GetElapsedTime() > 1.4f)
    {
        Animation* anim = ResourceManager::getAnimation("BlueOrb");
        anim->setScale(0.75f, 0.75f);
        shootAtPoint(tBullets, anim, 6, box.Left, screenH + 300, 300);
        shotTimer.Reset();
    }
}
///|/// --------- ///|///

///|/// Sidewinder ///|///
Sidewinder::Sidewinder(float x, float y, bool rev) : Enemy(rev)
{
    registerName("Sidewinder");
    Animation* tempAnim = ResourceManager::getAnimation("Rusty");
    tempAnim->setScale(0.75f, 0.75f);
    this->setSprite(tempAnim);
    calculateRect(x, y); //Set up how big our collision box is, based off the Animation
    boss = false; //Bosses don't die when they go out of range
    points = 5;
    speed = 200; //Pixels per Second
    health = 2;

    //Waypoints here
    setWPMode(WP_SINGLE);
    addWaypoint(screenW + 200, (int)box.Top);
    //End Waypoints

    shotTimer.Reset();
}

void Sidewinder::think(EnemyBulletFactory& tBullets)
{
    //Bullet Logic Here
    if(shotTimer.GetElapsedTime() > 0.5f)
    {
        Animation* anim = ResourceManager::getAnimation("BlueOrb");
        anim->setScale(0.75f, 0.75f);
        shootAtPoint(tBullets, anim, 6, screenW - 200, 400, 250);
        shotTimer.Reset();
    }
}
///|/// ---------- ///|///

///|/// Vampire_Outer ///|///
Vampire_Outer::Vampire_Outer(float x, float y, bool rev) : Enemy(rev)
{
    Animation* tempAnim = ResourceManager::getAnimation("Vampire");
    this->setSprite(tempAnim);
    this->calculateRect(x, y); //Set up how big our collision box is, based off the Animation
    boss = false; //Bosses don't die when they go out of range
    points = 40;
    speed = 120; //Pixels per Second
    health = 25;
    registerName("Vampire_Outer");

    //Waypoints here - Waypoints loop back to the first when they reach the end
    setWPMode(WP_SINGLE);
    for(int i = 1; i <= 5; i++)
    {
        addWaypoint( (int)box.Left - 240, (int)box.Bottom + (240 * i));
        addWaypoint( (int)box.Left + 240, (int)box.Bottom + (240 * (i + 1)));
    }
    //End Waypoints

    shotTimer.Reset();
}

void Vampire_Outer::think(EnemyBulletFactory& tBullets)
{
    if(shotTimer.GetElapsedTime() > 1.5f)
    {
        /*if(!reverse)
            shootAtPoint(tBullets, anim, 6, screenW - 200, 400, 250);
        else if(reverse)
            shootAtPoint(tBullets, anim, 6, 200, 400, 250);*/

        shootAtPoint(tBullets, ResourceManager::getAnimation("Redarang"), 6, box.Left, box.Top - 100, 200);
        if(!reverse)
        {
            shootAtPoint(tBullets, ResourceManager::getAnimation("Redarang"), 6, box.Left - 50, box.Top - 50, 200);
            shootAtPoint(tBullets, ResourceManager::getAnimation("Redarang"), 6, box.Left - 100, box.Top, 200);
            shootAtPoint(tBullets, ResourceManager::getAnimation("Redarang"), 6, box.Left - 120, box.Top + 140, 200);
        }
        else
        {
            shootAtPoint(tBullets, ResourceManager::getAnimation("Redarang"), 6, box.Left + 50, box.Top - 50, 200);
            shootAtPoint(tBullets, ResourceManager::getAnimation("Redarang"), 6, box.Left + 100, box.Top, 200);
            shootAtPoint(tBullets, ResourceManager::getAnimation("Redarang"), 6, box.Left + 120, box.Top + 140, 200);
        }

        shootAtPoint(tBullets, ResourceManager::getAnimation("Redarang"), 6, box.Left, box.Top + 240, 200);
        shotTimer.Reset();
    }
}
///|/// ------- ///|///

///|/// Vampire_Inner ///|///
Vampire_Inner::Vampire_Inner(float x, float y, bool rev) : Enemy(rev)
{
    Animation* tempAnim = ResourceManager::getAnimation("Vampire");
    this->setSprite(tempAnim);
    this->calculateRect(x, y); //Set up how big our collision box is, based off the Animation
    boss = false; //Bosses don't die when they go out of range
    points = 40;
    speed = 80; //Pixels per Second
    health = 45;
    registerName("Vampire_Inner");

    //Waypoints here - Waypoints loop back to the first when they reach the end
    setWPMode(WP_SINGLE);
    xVel = 0;
    yVel = speed;
    //End Waypoints

    shotTimer.Reset();
}

void Vampire_Inner::think(EnemyBulletFactory& tBullets)
{
    if(shotTimer.GetElapsedTime() > 1.5f)
    {
        shootAtPoint(tBullets, ResourceManager::getAnimation("Redarang"), 12, box.Left, box.Top - 100, 200);
        shootAtPoint(tBullets, ResourceManager::getAnimation("Redarang"), 12, box.Left - 50, box.Top - 50, 200);
        shootAtPoint(tBullets, ResourceManager::getAnimation("Redarang"), 12, box.Left - 100, box.Top, 200);
        shootAtPoint(tBullets, ResourceManager::getAnimation("Redarang"), 12, box.Left - 120, box.Top + 140, 200);
        shootAtPoint(tBullets, ResourceManager::getAnimation("Redarang"), 12, box.Left + 50, box.Top - 50, 200);
        shootAtPoint(tBullets, ResourceManager::getAnimation("Redarang"), 12, box.Left + 100, box.Top, 200);
        shootAtPoint(tBullets, ResourceManager::getAnimation("Redarang"), 12, box.Left + 120, box.Top + 140, 200);
        shootAtPoint(tBullets, ResourceManager::getAnimation("Redarang"), 12, box.Left, box.Top + 240, 200);
        shotTimer.Reset();
    }
}
///|/// ------------- ///|///

///|/// Blaster ///|///
Blaster::Blaster(float x, float y, bool rev) : Enemy(rev)
{
    Animation* tempAnim = ResourceManager::getAnimation("Blaster");
    this->setSprite(tempAnim);
    this->calculateRect(x, y); //Set up how big our collision box is, based off the Animation
    boss = false; //Bosses don't die when they go out of range
    points = 40;
    speed = 175; //Pixels per Second
    health = 15;
    registerName("Blaster");

    //Waypoints here - Waypoints loop back to the first when they reach the end
    setWPMode(WP_SINGLE);
    addWaypoint((screenW / 2) + 40, screenH / 2);
    addWaypoint(50, 50);
    addWaypoint(50, screenH + 200);
    //End Waypoints

    shotTimer.Reset();
}

void Blaster::think(EnemyBulletFactory& tBullets)
{
    if(shotTimer.GetElapsedTime() > 1.5f)
    {
        shootAtPoint(tBullets, ResourceManager::getAnimation("HawkBullet"), 4, screenW / 2, (screenH / 2) - 150, 200);
        shootAtPoint(tBullets, ResourceManager::getAnimation("HawkBullet"), 4, screenW / 2, screenH / 2, 200);
        shootAtPoint(tBullets, ResourceManager::getAnimation("HawkBullet"), 4, screenW / 2, (screenH / 2) + 150, 200);
        shotTimer.Reset();
    }
}
///|/// ------- ///|///

///|/// CircleStrafer ///|///
CircleStrafer::CircleStrafer(float x, float y, bool rev) : Enemy(rev)
{
    registerName("CircleStrafer");
    Animation* tempAnim = ResourceManager::getAnimation("Purple_Fighter");
    this->setSprite(tempAnim);
    this->calculateRect(x, y); //Set up how big our collision box is, based off the Animation
    boss = false;
    points = 20;
    speed = 160;
    health = 18;

    //Waypoints here
    setWPMode(WP_SINGLE);
    addWaypoint(screenW / 2, 20);
    addWaypoint((screenW / 2) + 20, screenH / 2);
    addWaypoint( (screenW / 2) + 50, screenH / 2);
    int radius = 150;
    for( int Y = -radius; Y <= radius; Y += 20 )
    {
        double X = sqrt ( ( radius * radius ) - ( Y * Y ) );
        addWaypoint((int)X + ((screenW / 2) + 50), Y + (screenH / 2));
    }
    addWaypoint( (screenW / 2) + 50, screenH + 150);
    //End Waypoints

    shotTimer.Reset();
}

void CircleStrafer::think(EnemyBulletFactory& tBullets)
{
    if(shotTimer.GetElapsedTime() > 0.3f)
    {
        float tarX = this->getX() - 50;
        float tarY = this->getY();
        shootAtPoint(tBullets, ResourceManager::getAnimation("BlueOrb"), 6, tarX, tarY, 200);
        shotTimer.Reset();
    }
}
///|/// ------------- ///|///

///|/// GreenFighter ///|///
GreenFighter::GreenFighter(float x, float y, bool rev) : Enemy(rev)
{
    registerName("Green_Fighter");
    Animation* tempAnim = ResourceManager::getAnimation("Green_Fighter");
    this->setSprite(tempAnim);
    this->calculateRect(x, y); //Set up how big our collision box is, based off the Animation
    boss = false;
    points = 30;
    speed = 200;
    health = 25;

    //Waypoints here
    setWPMode(WP_LOOP);
    addWaypoint((screenW / 2) + 30, (screenH / 2) + 30);
    addWaypoint((screenW / 2) + 30, (screenH / 2) + 60);
    addWaypoint((screenW / 2) + 30, (screenH / 2));
    addWaypoint((screenW / 2) - 30, (screenH / 2));
    addWaypoint((screenW / 2) + 60, (screenH / 2));
    addWaypoint((screenW / 2) + 30, (screenH / 2) + 30);
    //End Waypoints

    shotTimer.Reset();
}

void GreenFighter::think(EnemyBulletFactory& tBullets)
{
    if(shotTimer.GetElapsedTime() > 0.2f)
    {
        int radius = 150;

        static int Y = -radius;

        if(!(Y <= radius))
            Y = -radius;

        double X = sqrt ( ( radius * radius ) - ( Y * Y ) );
        float xCenter = ((box.Right - box.Left) / 2) + box.Left;
        float yCenter = ((box.Bottom - box.Top) / 2) + box.Top;
        shootAtPoint(tBullets, ResourceManager::getAnimation("Lazer"), 10, X + xCenter, Y + yCenter, 200);
        shootAtPoint(tBullets, ResourceManager::getAnimation("Lazer"), 10, (-X) + xCenter, (-Y) + yCenter, 200);

        Y += 5;
        shotTimer.Reset();
    }
}
///|/// ------------- ///|///
