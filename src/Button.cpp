#include "Button.h"

Button::~Button()
{

}

void Button::draw(sf::RenderWindow& game)
{
    if(active)
    {
        game.Draw(sprite_active);
        name.SetColor(sf::Color(237, 28, 26));
    }
    else if(pressed)
    {
        game.Draw(sprite_pressed);
        name.SetColor(sf::Color(0, 0, 0));
    }
    else if(!pressed)
    {
        game.Draw(sprite);
        name.SetColor(sf::Color(0, 0, 0));
    }

    game.Draw(name);
}

void Button::handlePressed(sf::Event& event)
{
    if(event.Type == sf::Event::MouseButtonPressed)
    {
        if( event.MouseButton.Button == sf::Mouse::Left )
        {
            if(box.Contains(event.MouseButton.X, event.MouseButton.Y))
            {
                this->pressed = true;
            }
        }
    }
    else if(event.Type == sf::Event::MouseButtonReleased)
    {
        if( event.MouseButton.Button == sf::Mouse::Left )
        {
            this->pressed = false;
        }
    }
}

void Button::handleEvents(sf::Event& event, Player& player)
{
    if(event.Type == sf::Event::MouseButtonReleased && box.Contains(event.MouseButton.X, event.MouseButton.Y))
        this->onClick(player);
}

void ChangeWeaponButton::onClick(Player& player)
{
    player.changeWeapon(weapon);
}

void ChangeWeaponButton::think(Player& player)
{
    if(player.getWeapon() == weapon)
        active = true;
    else
        active = false;
}

void ChangePowerButton::onClick(Player& player)
{
    player.changePower(power);
}

void ChangePowerButton::think(Player& player)
{
    if(player.getPower() == power)
        active = true;
    else
        active = false;
}
