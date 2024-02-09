#include "ButtonManager.h"

ButtonManager::ButtonManager()
{
    tButtons.reserve(15);
}

ButtonManager::~ButtonManager()
{
    tButtons.clear();
}

void ButtonManager::addButton(Button* b)
{
    tButtons.push_back(b);
}

void ButtonManager::handleEvents(sf::Event& event, Player& p)
{
    for(std::vector<Button*>::iterator mIter = tButtons.begin(); mIter != tButtons.end(); mIter++)
    {
        (*mIter)->handlePressed(event);
        (*mIter)->handleEvents(event, p);
    }
}
void ButtonManager::think(Player& p)
{
    for(std::vector<Button*>::iterator mIter = tButtons.begin(); mIter != tButtons.end(); mIter++)
    {
        (*mIter)->think(p);
    }
}

void ButtonManager::draw(sf::RenderWindow& game)
{
    for(std::vector<Button*>::iterator mIter = tButtons.begin(); mIter != tButtons.end(); mIter++)
    {
        (*mIter)->draw(game);
    }
}
