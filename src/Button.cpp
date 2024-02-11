#include "Button.h"

Button::Button(std::string Name, const sf::Image& Sprite, const sf::Image& Sprite_Pressed, const sf::Image& Sprite_active, int X, int Y, int W, int H)
{
    sprite.SetImage(Sprite);
    sprite_pressed.SetImage(Sprite_Pressed);
    sprite_active.SetImage(Sprite_active);

    font.LoadFromFile("Graphics/Consola.ttf", 12);

    name.SetText(Name);
    name.SetPosition(X + 10, Y + 2);
    name.SetSize(12);
    name.SetFont(font);

    sprite.SetPosition(X, Y);
    sprite_pressed.SetPosition(X, Y);
    sprite_active.SetPosition(X, Y);

    box.Left = X;
    box.Top = Y;
    box.Right = X + W;
    box.Bottom = Y + H;

    pressed = false;
    active = false;
}

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
