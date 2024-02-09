#ifndef BUTTONMANAGER_H_
#define BUTTONMANAGER_H_

//The ButtonManager class handles the buttons and ensures that they are drawn and can receive click events.
class ButtonManager
{
    private:
        std::vector<Button*> tButtons;

    public:
        ButtonManager();
        ~ButtonManager();

        void addButton(Button* b);
        void think(Player& p);
        void handleEvents(sf::Event& event, Player& p);
        void draw(sf::RenderWindow& game);
};

#endif // BUTTONMANAGER_H_
