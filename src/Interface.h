#ifndef INTERFACE_H_
#define INTERFACE_H_

#include "ButtonManager.h"
#include "TextRenderer.h"
#include "Player.h"

//Draws the entire interface.
class Interface
{
    private:
        float x, y, w, h;
        sf::FloatRect box;
        sf::Sprite background;
        sf::Sprite SelectionBase1;
        sf::Sprite SelectionBase2;
        sf::String BombText;
        sf::Sprite scoreNode;
        ButtonManager tButtons;

        sf::Sprite healthOverlay;
        sf::Sprite shieldOverlay;
        sf::Sprite BombCooldownBase;

        sf::Font font;
        TextRenderer* theText;

        float plyHP;
        float MaxPlyHP;
        float plyShields;
        int plyScore;
        float MaxPlyShields;
        float bombStatus;

    public:
        Interface();
        ~Interface();
        void handleEvents(sf::Event& events, Player& tPlayer);
        void think(Player& tPlayer, int& Score);
        void draw(sf::RenderWindow& game);
};

#endif // INTERFACE_H_
