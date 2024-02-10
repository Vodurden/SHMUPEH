#include "State_StartMenu.h"

State_StartMenu::State_StartMenu() :
    State(), StartMenu(sf::VideoMode(800, 500, 32), "Welcome to SHMUPEH")
{
    nextState = STATE_STARTMENU;
    StartMenu.SetFramerateLimit(60);
    StartImage.SetImage(ResourceManager::getImage("StartImage"));
}

void State_StartMenu::open()
{
    StartMenu.Create(sf::VideoMode(800, 500, 32), "Welcome to SHMUPEH");
    StartMenu.SetFramerateLimit(60);
}

void State_StartMenu::close()
{
    StartMenu.Close();
}

void State_StartMenu::handleEvents()
{
    sf::Event Event;
    while (StartMenu.GetEvent(Event))
    {
        // Close window : exit
        if (Event.Type == sf::Event::Closed)
            StartMenu.Close();

        if(Event.Type == sf::Event::MouseButtonPressed)
        {
            nextState = STATE_GAME;
        }

    }
}

void State_StartMenu::think() {}
void State_StartMenu::draw()
{
    StartMenu.Clear();
    StartMenu.Draw(StartImage);
    StartMenu.Display();
}
