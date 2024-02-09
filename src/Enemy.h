#ifndef ENEMY_H_
#define ENEMY_H_

// The Enemy is the base class for all enemies, it has no AI but contains all of the attributes of other enemies.
class Enemy
{
    private:
        Animation* sprite;
        Animation* explosion;
        WaypointMachine tWaypoints;
    protected:
        static int screenW, screenH;
        std::string name;
        sf::FloatRect box;
        float health, maxhealth;
        float speed;
        float xVel, yVel;
        float originX, originY;
        bool boss, reverse;

        void setSprite(Animation* Sprite);
        void calculateRect(float x, float y);
        void offset(float x, float y);
        sf::Color normColor;
        int points;
        sf::Clock shotTimer;
        sf::Clock colTimer;

        void damageEffect();
        void shootAtPoint(EnemyBulletFactory& tBullets, Animation* anim, int damage, float tarX, float tarY, float speed);
        void registerName(const std::string& Name) {name = Name;}
    public:
        Enemy(bool rev = false);
        Enemy(const Enemy& rhs);
        Animation* getExplosion() {return explosion;}
        static void giveScreenArgs(int w, int h) {screenW = w; screenH = h;}
        virtual ~Enemy();
        void reqThink(float deltaTicks); //Required Thoughts
        void draw(sf::RenderWindow& screen);
        void addWaypoint(const int x, const int y);
        void setWPMode(unsigned int WpMode) {tWaypoints.setMode(WpMode);}
        virtual void think(EnemyBulletFactory& tBullets) = 0; //Overloaded thoughts

        std::string getName() {return name;}
        void setHealth(float h) {health = h;}
        const sf::FloatRect& getBox() {return box;}
        int getScore() {return points;}
        void damage(float h);
        void damageByPercent(float p);
        float getHealth() {return health;}
        float getMaxHealth() {return maxhealth;}
        float getX() {return box.Left;}
        float getY() {return box.Top;}
        float getW() {return sprite->getW();}
        float getH() {return sprite->getH();}
        sf::Vector2f getScale() {return sprite->getScale();}
        bool isBoss() {return boss;}
};
//The Wanderer is an enemy implementation that flies around the screen in a clockwise or anti-clockwise pattern based on the value of ‘rev’, it fires at the center of the screen.
class Wanderer : public Enemy
{
    public:
        Wanderer(float x, float y, float WPX, float WPY, bool rev = false);
        Wanderer(const Enemy& rhs) : Enemy(rhs) {}
        void think(EnemyBulletFactory& tBullets);
};
// The Runstrike is an enemy implementation that flies in diagonally
class Runstrike : public Enemy
{
    public:
        Runstrike(float x, float y, bool rev = false);
        Runstrike(const Enemy& rhs) : Enemy(rhs) {}
        void think(EnemyBulletFactory& tBullets);
};
//Flys in from the side, fires down
class Sidewinder : public Enemy
{
    public:
        Sidewinder(float x, float y, bool rev = false);
        Sidewinder(const Enemy& rhs) : Enemy(rhs) {}
        void think(EnemyBulletFactory& tBullets);
};
//Boss Enemy, flys down and shoots hard-hitting missles
class Vampire_Outer : public Enemy
{
    public:
        Vampire_Outer(float x, float y, bool rev = false);
        Vampire_Outer(const Enemy& rhs) : Enemy(rhs) {}
        void think(EnemyBulletFactory& tBullets);
};
//Similar to Vampire_Outer but moves back and forth in a pattern
class Vampire_Inner : public Enemy
{
    public:
        Vampire_Inner(float x, float y, bool rev = false);
        Vampire_Inner(const Enemy& rhs) : Enemy(rhs) {}
        void think(EnemyBulletFactory& tBullets);
};
//Flies straight down and fires straight down
class Blaster : public Enemy
{
    public:
        Blaster(float x, float y, bool rev = false);
        Blaster(const Enemy& rhs) : Enemy(rhs) {}
        void think(EnemyBulletFactory& tBullets);
};
//Flies into the middle and circles around, shoots in 8 directions
class CircleStrafer : public Enemy
{
    public:
        CircleStrafer(float x, float y, bool rev = false);
        CircleStrafer(const Enemy& rhs) : Enemy(rhs) {}
        void think(EnemyBulletFactory& tBullets);
};
// Fires spinning lazers, moves in a box
class GreenFighter : public Enemy
{
    public:
        GreenFighter(float x, float y, bool rev = false);
        GreenFighter(const Enemy& rhs) : Enemy(rhs) {}
        void think(EnemyBulletFactory& tBullets);
};

#endif // ENEMY_H_
