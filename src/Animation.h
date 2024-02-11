#ifndef ANIMATION_H_
#define ANIMATION_H_

#include <SFML/Graphics.hpp>

// The animation class holds and animates a sprite, it is interchangeable with sprites.
class Animation
{
    private:
        sf::Sprite sprite;
        sf::FloatRect clip; //The size of each animation frame
        sf::Clock timer; //Times each animation stage
        int curFrame, maxFrames;
        float frameInterval;
        bool started;
        bool loop;

    public:
        Animation(const sf::Image& Image, const int frW, const int frH, const float timeBetweenFrames, const int maxFrames, bool Loop = true);
        Animation(const Animation& rhs);
        void start() {
          started = true;
          curFrame = 0;
          timer.Reset();
        }
        void stop(){started = false;}
        void setLoop(bool l) {loop = l;}

        void think();
        void draw(float X, float Y, sf::RenderWindow& game);

        float getW() {return ((clip.Right - clip.Left) * sprite.GetScale().x);}
        float getH() {return ((clip.Bottom - clip.Top) * sprite.GetScale().y);}
        float getFrameInterval() {return frameInterval;}
        sf::Vector2f getScale() {return sprite.GetScale();}
        sf::IntRect getSubRect() {return sprite.GetSubRect();}
        int getMaxFrames() {return maxFrames;}
        float getX() {return sprite.GetPosition().x;}
        float getY() {return sprite.GetPosition().y;}
        float getRotation() {return sprite.GetRotation();}
        bool getLoop() {return loop;}

        sf::FloatRect getClip() {return clip;}
        sf::Color getColor() {return sprite.GetColor();}
        sf::Vector2f TransformToGlobal(const sf::Vector2f &Point) const {return sprite.TransformToGlobal(Point);}

        //Manipulation Commands
        void setColor(const int r, const int g, const int b, const int a){sprite.SetColor(sf::Color(r, g, b, a));}
        void setColor(sf::Color c) {sprite.SetColor(c);}
        void setX(const float x) {sprite.SetX(x);}
        void setY(const float y) {sprite.SetY(y);}
        void setCenter(float x, float y) {sprite.SetCenter(x, y);}
        void setPoisiton(const float x, const float y) {sprite.SetPosition(x, y);}
        void setRotation(const float ang) {sprite.SetRotation(ang);}
        void setScale(const float scaleX, const float scaleY);
        void setBlendMode(const sf::Blend::Mode mode) {sprite.SetBlendMode(mode);}
        void move(const float x, const float y) {sprite.Move(x, y);}
        void rotate(const float deg) {sprite.Rotate(deg);}
        void scale(const float facX, const float facY) {sprite.Scale(facX, facY);}
        bool isDone() { return (loop == false && curFrame == maxFrames - 1); }
};

#endif // ANIMATION_H_
