#include "Interface.h"

#include <sstream>

Interface::Interface()
{
    x = 0.0f;
    y = 630.0f; //22
    w = 1024.0f;
    h = 90.0f;
    box.Left = x;
    box.Top = y;
    box.Right = box.Left + w;
    box.Bottom = box.Top + h;

    background.SetImage(ResourceManager::getImage("Interface_Background"));
    SelectionBase1.SetImage(ResourceManager::getImage("SelectionBase"));
    SelectionBase2.SetImage(ResourceManager::getImage("SelectionBase"));
    scoreNode.SetImage(ResourceManager::getImage("ScoreNode"));
    theText = new TextRenderer("Graphics/Consola.ttf", 12, sf::Color(255, 200, 150));

    background.SetPosition(x, y);
    healthOverlay.SetPosition(x + 142, y + 8);
    shieldOverlay.SetPosition(x + 124, y + 49);
    scoreNode.SetPosition(x + 817, y + 12);

    theText->addStaticText("Main Weapon", 600, 626);
    SelectionBase1.SetPosition(x + 583, y + 2);

    theText->addStaticText("Power", 738, 626);
    SelectionBase2.SetPosition(x + 696, y + 2);

    font.LoadFromFile("Graphics/Consola.ttf", 12);

    healthOverlay.SetImage(ResourceManager::getImage("HealthSegment"));
    shieldOverlay.SetImage(ResourceManager::getImage("ShieldSegment"));

    tButtons.addButton(new ChangeWeaponButton(WEAPON_FORWARD, "Laser",
                                            ResourceManager::getImage("Button_Unpressed"),
                                            ResourceManager::getImage("Button_Pressed"),
                                            ResourceManager::getImage("Button_Active"),
                                            587, 641, 106, 20));

    tButtons.addButton(new ChangeWeaponButton(WEAPON_DIAGONAL, "Energy Orb",
                                            ResourceManager::getImage("Button_Unpressed"),
                                            ResourceManager::getImage("Button_Pressed"),
                                            ResourceManager::getImage("Button_Active"),
                                            587, 663, 106, 20));

    tButtons.addButton(new ChangeWeaponButton(WEAPON_BROADSIDE, "Burn Cannon",
                                        ResourceManager::getImage("Button_Unpressed"),
                                        ResourceManager::getImage("Button_Pressed"),
                                        ResourceManager::getImage("Button_Active"),
                                        587, 685, 106, 20));

    tButtons.addButton(new ChangePowerButton(ENERGY_SHIELD, "Shields",
                                        ResourceManager::getImage("Button_Unpressed"),
                                        ResourceManager::getImage("Button_Pressed"),
                                        ResourceManager::getImage("Button_Active"),
                                        701, 663, 106, 20));

    tButtons.addButton(new ChangePowerButton(ENERGY_WEAPONS, "Weapons",
                                        ResourceManager::getImage("Button_Unpressed"),
                                        ResourceManager::getImage("Button_Pressed"),
                                        ResourceManager::getImage("Button_Active"),
                                        701, 641, 106, 20));

    tButtons.addButton(new ChangePowerButton(ENERGY_ENGINES, "Engines",
                                        ResourceManager::getImage("Button_Unpressed"),
                                        ResourceManager::getImage("Button_Pressed"),
                                        ResourceManager::getImage("Button_Active"),
                                        701, 685, 106, 20));
}

Interface::~Interface()
{

}

void Interface::handleEvents(sf::Event& events, Player& tPlayer)
{
    tButtons.handleEvents(events, tPlayer);

    if(events.Type == sf::Event::KeyPressed)
    {
        switch(events.Key.Code)
        {
            case sf::Key::Q: tPlayer.changeWeapon(WEAPON_FORWARD); break;
            case sf::Key::A: tPlayer.changeWeapon(WEAPON_DIAGONAL); break;
            case sf::Key::Z: tPlayer.changeWeapon(WEAPON_BROADSIDE); break;

            case sf::Key::W: tPlayer.changePower(ENERGY_WEAPONS); break;
            case sf::Key::S: tPlayer.changePower(ENERGY_SHIELD); break;
            case sf::Key::X: tPlayer.changePower(ENERGY_ENGINES); break;
            default:;
        }
    }
}

void Interface::think(Player& tPlayer, int& Score)
{
    plyHP = tPlayer.getHealth();
    plyShields = tPlayer.getShields();
    plyScore = Score;
    MaxPlyHP = tPlayer.getMaxHealth();
    MaxPlyShields = tPlayer.getMaxShields();
    tButtons.think(tPlayer);
}

void Interface::draw(sf::RenderWindow& game)
{
    game.Draw(background);
    //Health Display
    sf::Vector2f healthPos = healthOverlay.GetPosition();
    sf::Shape underlay = sf::Shape::Rectangle(healthPos.x, healthPos.y, healthPos.x + (4.17f * ((plyHP / MaxPlyHP) * 100)), healthPos.y + 36, sf::Color(0, 255, 0));
    game.Draw(underlay);
    game.Draw(healthOverlay);

    std::ostringstream o;
    o << "Health: " << plyHP << "/" << MaxPlyHP << " (" << ceil((plyHP / MaxPlyHP) * 100)  << "%)";
    sf::String hpStr(o.str());
    hpStr.SetPosition(healthPos.x + 114, healthPos.y + 7);
    hpStr.SetFont(font);
    hpStr.SetSize(15);
    hpStr.SetColor(sf::Color(255, 0, 0));
    game.Draw(hpStr);

    //Shield Display
    sf::Vector2f shieldPos = shieldOverlay.GetPosition();
    sf::Shape shunderlay = sf::Shape::Rectangle(shieldPos.x, shieldPos.y, shieldPos.x + (4.19f * ((plyShields / MaxPlyShields) * 100)), shieldPos.y + 36, sf::Color(0, 255, 255));
    game.Draw(shunderlay);
    game.Draw(shieldOverlay);
    std::ostringstream f;
    f << "Shield: " << plyShields << "/" << MaxPlyShields << " (" << ceil((plyShields / MaxPlyShields) * 100)  << "%)";
    sf::String spStr(f.str());
    spStr.SetPosition(shieldPos.x + 114, shieldPos.y + 7);
    spStr.SetFont(font);
    spStr.SetSize(15);
    spStr.SetColor(sf::Color(255, 0, 0));
    game.Draw(spStr);

    game.Draw(SelectionBase1);
    game.Draw(SelectionBase2);
    game.Draw(scoreNode);

    tButtons.draw(game);
    theText->draw(game);

    //Score Display
    sf::Vector2f scorePos = scoreNode.GetPosition();
    std::ostringstream scoreD;
    scoreD << "Score: " << plyScore;
    sf::String scoreStr(scoreD.str());
    scoreStr.SetPosition(scorePos.x + 31, scorePos.y + 14);
    scoreStr.SetFont(font);
    scoreStr.SetSize(15);
    scoreStr.SetColor(sf::Color(14, 218, 228));
    game.Draw(scoreStr);
}
