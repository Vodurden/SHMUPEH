#ifndef BULLET_H_
#define BULLET_H_

// Bullets are objects that are shot by enemies and players and can damage things, they do not handle their own collision
class Bullet
{
    protected:
        Animation* sprite;
        sf::FloatRect box;
        float x, y;
        float w, h, xVel, yVel;
        float damage;

    public:
        Bullet(Animation* anim, float Damage, float X, float Y, float W, float H, float XVel, float YVel);
        Bullet(const Bullet& rhs);
        virtual ~Bullet();

        float getX() {return box.Left;}
        float getY() {return box.Top;}
        float getDamage() {return damage;}
        sf::FloatRect& getBox() {return box;}
        void setScale(float xfac, float yfac);
        bool intersects(sf::FloatRect other) {return box.Intersects(other);}

        virtual void think(float deltaTicks);
        virtual void draw(sf::RenderWindow& game);
};

#endif // BULLET_H_
