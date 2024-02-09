#ifndef BULLETFACTORY_H_
#define BULLETFACTORY_H_

//BulletFactories manage an array of bullets, they handle bullet movement and collision.
class BulletFactory
{
    private:
        static int gameW, gameH;

        std::vector<Bullet*> tBullets;
        int bulletCount;

        TextRenderer* damageRender;

    public:
        BulletFactory();
        ~BulletFactory();

        void addBullet(Bullet* base);
        void think(float deltaTicks, std::vector<Enemy*>& enemies);
        void draw(sf::RenderWindow& game);
        void reset();

        const int* getBulletCount() {return &bulletCount;}

        static void giveScreenArgs(int w, int h) {gameW = w; gameH = h;}
};


#endif // BULLETFACTORY_H_
