#include "Animation.h"

void Animation::think()
{
    if(started == true)
    {
        if(timer.GetElapsedTime() >= frameInterval)
        {
                if(curFrame < endFrame)
                {
                    clip.Offset(clip.GetWidth(), 0);
                    curFrame += 1;
                }
                else
                {
                    if(loop)
                    {
                        clip.Offset(-(clip.GetWidth() * (endFrame - 1)),0); //Move back to the start
                        curFrame = 1;
                    }
                }

            sprite.SetSubRect(sf::IntRect((int)clip.Left, (int)clip.Top, (int)clip.Right, (int)clip.Bottom));
            timer.Reset();
        }
    }
}

Animation::Animation(const sf::Image& Image, const int frW, const int frH, const float timeBetweenFrames, const int maxFrames, bool Loop)
{
    sprite.SetImage(Image);
    curFrame = 1;
    frameInterval = timeBetweenFrames;
    endFrame = maxFrames;
    started = false;

    clip.Left = 0;
    clip.Top = 0;
    clip.Bottom = frH;
    clip.Right = frW;

    sprite.SetSubRect(sf::IntRect((int)clip.Left, (int)clip.Top, (int)clip.Right, (int)clip.Bottom));

    loop = Loop;
}

Animation::Animation(const Animation& rhs)
{
    sprite.SetImage(*(rhs.sprite.GetImage()));
    sprite.SetScale(rhs.sprite.GetScale());
    sprite.SetCenter(rhs.sprite.GetCenter());
    curFrame = rhs.curFrame;
    frameInterval = rhs.frameInterval;
    endFrame = rhs.endFrame;
    started = rhs.started;

    clip.Left = rhs.clip.Left;
    clip.Top = rhs.clip.Top;
    clip.Bottom = rhs.clip.Bottom;
    clip.Right = rhs.clip.Right;

    sprite.SetSubRect(sf::IntRect((int)clip.Left, (int)clip.Top, (int)clip.Right, (int)clip.Bottom));

    loop = rhs.loop;
}

void Animation::draw(float X, float Y, sf::RenderWindow& game)
{
    sprite.SetX(X);
    sprite.SetY(Y);
    game.Draw(sprite);
}

void Animation::setScale(const float scaleX, const float scaleY)
{
    sprite.SetScale(scaleX, scaleY);
}
