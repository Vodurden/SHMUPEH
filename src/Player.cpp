#include "Player.h"

int Player::screenW = 0;
int Player::screenH = 0;

Player::Player(float X, float Y, sf::RenderWindow& game) : Input(game.GetInput())
{
    spriteSheet = ResourceManager::getAnimation("Player");
    spriteSheet->setX(X);
    spriteSheet->setY(Y);
    spriteSheet->setScale(1.5f, 1.5f);
    spriteSheet->start();
    normColor = spriteSheet->getColor();

    box.Top = Y;
    box.Left = X;
    box.Right = X + spriteSheet->getW();
    box.Bottom = Y + spriteSheet->getH();
    xPos = X;
    yPos = Y;

    startPosX = X;
    startPosY = Y;
    speed = 300;
    normspeed = speed;

    health = 75;
    shield = 25;
    maxhealth = health;
    maxshield = shield;

    weapon = WEAPON_FORWARD;
    power = ENERGY_WEAPONS;
    score = 0;

    timeBetweenShots = 1.0f;
}

void Player::reset()
{
    spriteSheet->setX(startPosX);
    spriteSheet->setY(startPosY);
    xPos = startPosX;
    yPos = startPosY;
    box.Top = startPosY;
    box.Left = startPosX;
    box.Right = startPosX + spriteSheet->getW();
    box.Bottom = startPosY + spriteSheet->getH();

    health = maxhealth;
    shield = maxshield;

    weapon = WEAPON_FORWARD;
    power = ENERGY_WEAPONS;
    score = 0;

    timeBetweenShots = 1.0f;
}

void Player::think(float deltaTicks, BulletFactory& bFactory, EnemyFactory& tEnemies)
{
    //Generate Input From KeyEvents
    float xVel = 0;
    float yVel = 0;

    //Movement
    float rSpeed = speed;

    if(Input.IsKeyDown(sf::Key::LShift))
    {
        float w = spriteSheet->getW();
        float h = spriteSheet->getH();
        spriteSheet->setColor(sf::Color(240, 240, 240, 120));
        rSpeed = speed * 0.3f;
        box.Left = xPos + (w * 0.38f);
        box.Right = (xPos + w) - (w * 0.38f);
        box.Top = yPos + (h * 0.38f);
        box.Bottom = (yPos + h) - (h * 0.38f);
        graze = true;
    }
    else
    {
        if(graze == true)
        {
            spriteSheet->setColor(normColor);
            box.Top = spriteSheet->getY();
            box.Left = spriteSheet->getX();
            box.Right = box.Left + spriteSheet->getW();
            box.Bottom = box.Top + spriteSheet->getH();
            speed = normspeed;
            graze = false;
        }
    }

    if(power == ENERGY_ENGINES)
        rSpeed *= 1.5f;

    if(Input.IsKeyDown(sf::Key::Left))
        xVel -= rSpeed;
    if(Input.IsKeyDown(sf::Key::Right))
        xVel += rSpeed;
    if(Input.IsKeyDown(sf::Key::Up))
        yVel -= rSpeed;
    if(Input.IsKeyDown(sf::Key::Down))
        yVel += rSpeed;

    //Shooting
    if(shotTimer.GetElapsedTime() > timeBetweenShots)
    {
        float damageMult = 1.0f;
        if(power == ENERGY_WEAPONS)
            damageMult = 1.5f;

        switch(weapon)
        {
            case WEAPON_FORWARD:
            {
                float X1 = xPos;
                float X2 = xPos + spriteSheet->getW() - 10; //(x + w) - 10;
                float Y = yPos;
                timeBetweenShots = 0.15f;

                //We need two because each getAnimation call produces a new animation
                Animation* anim1 = ResourceManager::getAnimation("Rapid_Bullet");
                Animation* anim2 = ResourceManager::getAnimation("Rapid_Bullet");
                bFactory.addBullet(new Bullet(anim1, 2.0f * damageMult, X1, Y, anim1->getW(), anim1->getH(), 0.0f, -600.0f));
                bFactory.addBullet(new Bullet(anim2, 2.0f * damageMult, X2, Y, anim2->getW(), anim2->getH(), 0.0f, -600.0f));
                break;
            }

            case WEAPON_DIAGONAL:
            {
                float X1 = xPos;
                float X2 = xPos + spriteSheet->getW() - 10;
                float Y = yPos;
                timeBetweenShots = 0.2f;
                Animation* anim1 = ResourceManager::getAnimation("YellowOrb");
                Animation* anim2 = ResourceManager::getAnimation("YellowOrb");
                bFactory.addBullet(new Bullet(anim1, 3.3f * damageMult, X1, Y, anim1->getW(), anim1->getH(), -300.0f, -300.0f));
                bFactory.addBullet(new Bullet(anim2, 3.3f * damageMult, X2, Y, anim2->getW(), anim2->getH(), 300.0f, -300.0f));
                break;
            }

            case WEAPON_BROADSIDE:
            {
                float X1 = xPos;
                float X2 = xPos + spriteSheet->getW() - 10;
                float Y = yPos;
                timeBetweenShots = 0.4f;
                Animation* anim1 = ResourceManager::getAnimation("Broadside_Left");
                Animation* anim2 = ResourceManager::getAnimation("Broadside_Right");
                bFactory.addBullet(new Bullet(anim1, 5.0f * damageMult, X1, Y, anim1->getW(), anim1->getH(), -600.0f, 0.0f));
                bFactory.addBullet(new Bullet(anim2, 5.0f * damageMult, X2, Y, anim2->getW(), anim2->getH(), 600.0f, 0.0f));
                break;
            }
        }

            shotTimer.Reset();
    }

    //Ship Collision
    //Collision with Enemies
    /*std::vector<Enemy*> enm = tEnemies.getEnemies();
    for(std::vector<Enemy*>::iterator mIter = enm.begin(); mIter != enm.end(); ++mIter)
    {
        if( this->intersects((*mIter)->getBox() ) )
        {
            //Damage is calculated based on how large we are vs. how large the enemy is
            //If we are of the same size we both should die.
            //This formula was tested in the CollisionDamageTester_SHMUPEH project, check the devlog
            //for more details
            float plySize = (box.Right - box.Left) * (box.Bottom - box.Top);
            sf::FloatRect tbox = (*mIter)->getBox();
            float enmSize = (tbox.Right - tbox.Left) * (tbox.Bottom - tbox.Top);
            float PSES = plySize / enmSize;
            float ESPS = enmSize / plySize;

            this->damageByPercent( ESPS * 100 );
            (*mIter)->damageByPercent( PSES * 100);
        }
    }*/

    //Shield
    if(shield < maxshield)
    {
        if(shieldTimer.GetElapsedTime() > 1.0f)
        {
            if(power == ENERGY_SHIELD)
                shield += 2;
            else
                shield += 1;

            shieldTimer.Reset();
        }
    }
    else if(shield >= maxshield)
    {
        shield = maxshield;
    }

    //Movement per Frame
    float offsetX = xVel * deltaTicks;
    float offsetY = yVel * deltaTicks;
    this->offset(offsetX, offsetY);
    spriteSheet->think();
}

void Player::offset(float X, float Y)
{
    box.Offset(X, Y);
    xPos += X;
    yPos += Y;

    float xOffset = 0, yOffset = 0;
    if(box.Right > screenW) {xOffset = screenW + (box.Right * -1);}
    if(box.Bottom > screenH) {yOffset = screenH + (box.Bottom * -1);}
    if(box.Left < 0) {xOffset = box.Left * -1;}
    if(box.Top < 0) {yOffset = box.Top * -1;}
    box.Offset(xOffset, yOffset);
    xPos += xOffset;
    yPos += yOffset;
}

void Player::draw(sf::RenderWindow& game)
{
    spriteSheet->draw(xPos, yPos, game);
    if(graze == true)
    {
        sf::Shape Rect = sf::Shape::Rectangle(box.Left, box.Top, box.Right, box.Bottom, sf::Color(255, 0, 0), 1, sf::Color(255, 255, 255));
        Rect.EnableFill(false);
        game.Draw(Rect);
    }
}

void Player::setScale(float X, float Y)
{
    spriteSheet->setScale(X, Y);
    float x = box.Left;
    float y = box.Top;
    box = spriteSheet->getClip();
    box.Right *= X;
    box.Bottom *= Y;
    box.Offset(x, y);
    xPos += x;
    yPos += y;
}

void Player::damage(float d)
{
    if(shield > d)
    {
        shield -= d;
    }
    else if (shield <= d)
    {
        float nDamage = d - shield;
        health -= nDamage;
        shield = 0;
    }
}

void Player::damageByPercent(float h)
{
    float damage = (maxhealth * h) / 100;
    if(shield > damage)
    {
        shield -= damage;
    }
    else if(shield <= damage)
    {
        float nDamage = damage - shield;
        health -= nDamage;
        shield = 0;
    }
}
