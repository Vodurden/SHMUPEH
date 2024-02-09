#include "Interface.h"

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
    theText = new TextRenderer("Graphics/consola.ttf", 12, sf::Color(255, 200, 150));
    theText->addStaticText("Main Weapon", 600, 626);
    theText->addStaticText("Power", 738, 626);

    scoreNode.SetPosition(815, 635);
    background.SetPosition(x, y);
    SelectionBase1.SetPosition(586, 625);
    SelectionBase2.SetPosition(700, 625);
    healthOverlay.SetPosition(145, 631);
    shieldOverlay.SetPosition(127, 674);

    font.LoadFromFile("Graphics/consola.ttf", 12);

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
    sf::Shape underlay = sf::Shape::Rectangle(145, 631, 145 + (4.17f * ((plyHP / MaxPlyHP) * 100)), 631 + 36, sf::Color(0, 255, 0));
    game.Draw(underlay);
    game.Draw(healthOverlay);

    std::ostringstream o;
    o << "Health: " << plyHP << "/" << MaxPlyHP << " (" << ceil((plyHP / MaxPlyHP) * 100)  << "%)";
    sf::String hpStr(o.str());
    hpStr.SetPosition(255, 640);
    hpStr.SetFont(font);
    hpStr.SetSize(15);
    hpStr.SetColor(sf::Color(255, 0, 0));
    game.Draw(hpStr);

    //Shield Display
    sf::Shape shunderlay = sf::Shape::Rectangle(127, 674, 127 + (4.19f * ((plyShields / MaxPlyShields) * 100)), 674 + 37, sf::Color(0, 255, 255));
    game.Draw(shunderlay);
    game.Draw(shieldOverlay);
    std::ostringstream f;
    f << "Shield: " << plyShields << "/" << MaxPlyShields << " (" << ceil((plyShields / MaxPlyShields) * 100)  << "%)";
    sf::String spStr(f.str());
    spStr.SetPosition(235, 683);
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
    std::ostringstream scoreD;
    scoreD << "Score: " << plyScore;
    sf::String scoreStr(scoreD.str());
    scoreStr.SetPosition(843, 647);
    scoreStr.SetFont(font);
    scoreStr.SetSize(15);
    scoreStr.SetColor(sf::Color(14, 218, 228));
    game.Draw(scoreStr);
}
