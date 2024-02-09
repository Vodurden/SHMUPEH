#ifndef ENEMYBULLETFACTORY_H_
#define ENEMYBULLETFACTORY_H_

class Player;
class Bullet;
//Handles updating the collisions and movement of all enemy bullets.
class EnemyBulletFactory
{
    private:
        static int gameW, gameH;

        std::vector<Bullet*> tBullets;
        int bulletCount;

    public:
        EnemyBulletFactory();
        ~EnemyBulletFactory();

        void addBullet(Bullet* base);
        void think(float deltaTicks, Player& tPlayer);
        void draw(sf::RenderWindow& game);
        void reset() {tBullets.clear();}

        int* getBulletCount() {return &bulletCount;}

        static void giveScreenArgs(int w, int h) {gameW = w; gameH = h;}
};

#endif // ENEMYBULLETFACTORY_H_
