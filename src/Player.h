#ifndef PLAYER_H_
#define PLAYER_H_

enum {WEAPON_FORWARD, WEAPON_DIAGONAL, WEAPON_BROADSIDE};
enum {ENERGY_WEAPONS, ENERGY_SHIELD, ENERGY_ENGINES};

//Defines everything to do with the player, movement, shooting, health, shields, changing weapons, etc…
class Player
{
    private:
        static int screenW, screenH;

        Animation* spriteSheet;
        sf::Color normColor;
        sf::FloatRect box;
        sf::Clock shieldTimer;
        sf::Clock shotTimer;
        const sf::Input& Input;

        float xPos, yPos;
        float health, maxhealth, shield, maxshield;
        int weapon, power;
        int score;
        float timeBetweenShots;
        bool graze;

        float startPosX, startPosY;
        float speed, normspeed;

    public:
        static void giveScreenArgs(int w, int h) {screenW = w; screenH = h;}

        Player(float X, float Y, sf::RenderWindow& game);
        void think(float deltaTicks, BulletFactory& bFactory, EnemyFactory& tEnemies);
        void draw(sf::RenderWindow& game);
        void reset();

        float getHealth() {return health;}
        float getShields() {return shield;}
        float getMaxHealth() {return maxhealth;}
        float getMaxShields() {return maxshield;}
        int getScore() {return score;}
        int getWeapon() {return weapon;}
        int getPower() {return power;}
        bool intersects(const sf::FloatRect& other) {return box.Intersects(other);}
        void setShields(float s) {shield = s;}
        void setScale(float X, float Y);
        void damage(float d);
        void damageByPercent(float d);
        void changeWeapon(int w) {weapon = w;}
        void changePower(int p) {power = p;}
        void offset(float X, float Y);
};

#endif // PLAYER_H_
