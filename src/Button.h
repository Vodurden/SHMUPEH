#ifndef BUTTON_H_
#define BUTTON_H_

//Buttons are clickable objects on the screen, in SHMUPEHs case they control the weapon and power selection.
class Button
{
    protected:
        sf::Sprite sprite;
        sf::Sprite sprite_pressed;
        sf::Sprite sprite_active;
        sf::Font font;
        sf::String name;
        sf::IntRect box;

        bool pressed;
        bool active;

    public:
        Button(std::string Name, const sf::Image& Sprite, const sf::Image& Sprite_Pressed, const sf::Image& Sprite_active, int X, int Y, int W, int H);
        virtual ~Button();
        virtual void onClick(Player& player) = 0;
        virtual void think(Player& p) = 0;
        virtual void handlePressed(sf::Event& event);
        virtual void handleEvents(sf::Event& event, Player& player);
        virtual void draw(sf::RenderWindow& game);
        virtual sf::IntRect getBox() {return box;}
};

class ChangeWeaponButton : public Button
{
    private:
        int weapon;

    public:
        ChangeWeaponButton(int Weapon, std::string Name, const sf::Image& Sprite, const sf::Image& Sprite_Pressed, const sf::Image& Sprite_Active, int X, int Y, int W, int H) : Button(Name, Sprite, Sprite_Pressed, Sprite_Active, X, Y, W, H) {weapon = Weapon;}
        void onClick(Player& player);
        void think(Player& player);
};

class ChangePowerButton : public Button
{
    private:
        int power;

    public:
        ChangePowerButton(int Power, std::string Name, const sf::Image& Sprite, const sf::Image& Sprite_Pressed, const sf::Image& Sprite_Active, int X, int Y, int W, int H) : Button(Name, Sprite, Sprite_Pressed, Sprite_Active, X, Y, W, H) {power = Power;}

        void onClick(Player& player);
        void think(Player& player);
};

#endif // BUTTON_H_
