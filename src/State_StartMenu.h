#ifndef STATE_STARTMENU_H_
#define STATE_STARTMENU_H_

#include <SFML/Graphics.hpp>

// The starting menu, with all the help information.
class State_StartMenu : public State
{
    private:
        sf::RenderWindow StartMenu;
        ButtonManager tButtons;
        sf::Sprite StartImage;
    public:
        State_StartMenu();
        void handleEvents();
        void think();
        void draw();
        bool isActive() {return StartMenu.IsOpened();}

        void open();
        void close();
};

#endif // STATE_STARTMENU_H_
