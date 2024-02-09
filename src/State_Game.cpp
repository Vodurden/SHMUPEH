#include "State_Game.h"

State_Game::State_Game() :
    State(), screenW(1024), screenH(720), gameW(1024), gameH(630),
    Game(sf::VideoMode(screenW, screenH, 32), "SHMUPEH"),
    tRender("Graphics/Consola.ttf", 16, sf::Color(150, 200, 250)),
    tPlayer(screenW / 2, screenH - (screenH * 0.25f), Game), tEnemies(&tPlayer),
    tLevels(tEnemies)
{
    Game.SetFramerateLimit(60);
    nextState = STATE_GAME;
    score = 0;

    Logger::log("Initializing Static Data...", LOGTYPE_TRIVIAL, LINEBREAK_N);
    Player::giveScreenArgs(gameW, gameH);
    BulletFactory::giveScreenArgs(gameW, gameH);
    TextRenderer::giveScreenArgs(gameW, gameH);
    EnemyManager::giveScreenArgs(gameW, gameH);
    Logger::log("Done", LOGTYPE_TRIVIAL);

    LevelMachine::addWavePool(new WandererWave(tEnemies));
    LevelMachine::addWavePool(new RunstrikeWave(tEnemies));
    LevelMachine::addWavePool(new SidewinderWave(tEnemies));
    LevelMachine::addWavePool(new VampireWave(tEnemies));
    LevelMachine::addWavePool(new BlasterWave(tEnemies));
    LevelMachine::addWavePool(new CircleStraferWave(tEnemies));
    LevelMachine::addWavePool(new GreenFighterWave(tEnemies));
}

void State_Game::open()
{
    Game.Create(sf::VideoMode(screenW, screenH, 32), "SHMUPEH");
}

void State_Game::close()
{
    Game.Close();
}

void State_Game::handleEvents()
{
    sf::Event Event;
    while (Game.GetEvent(Event))
    {
        // Close window : exit
        if (Event.Type == sf::Event::Closed)
            Game.Close();
        if (Event.Type == sf::Event::KeyPressed && Event.Key.Code == sf::Key::F5)
        {
            //Extrodinarily hacky code, but it works. Saves a screenshot
            //Into the screenshot folder with the form
            // "Screenshots/SHMUPEH_(MONTH)(DAY)(YEAR)_(HOUR)(MINUTE)(SECOND)"
            // Replacing the ()'s with their respective values
            sf::Image Screen = Game.Capture();
            char dateStr [9];
            char timeStr [9];
            _strdate( dateStr);
            _strtime( timeStr );
            std::stringstream screenShotPath;
            screenShotPath << "Screenshots/SHMUPEH_" << dateStr << "_" << timeStr << ".jpg";
            std::string myStr = screenShotPath.str();
            for(std::string::iterator mIter = myStr.begin() + 12; mIter != myStr.end();)
            {
                if(*mIter == ':' || *mIter == '/')
                {
                    mIter = myStr.erase(mIter);
                }
                else
                {
                    mIter++;
                }
            }
            Screen.SaveToFile(myStr);
        }

        tInterface.handleEvents(Event, tPlayer);
    }
}

void State_Game::think()
{
    tPlayer.think(deltaTimer.GetElapsedTime(), plyBulletFactory, tEnemies.GetEnemyFactory());
    tEnemies.think(deltaTimer.GetElapsedTime(), score);
    tInterface.think(tPlayer, score);
    plyBulletFactory.think(deltaTimer.GetElapsedTime(), tEnemies.GetEnemyFactory().getEnemies());
    tRender.think();
    tLevels.think();
    deltaTimer.Reset();

    if(tPlayer.getHealth() < 0)
    {
        tPlayer.reset();
        plyBulletFactory.reset();
        tEnemies.reset();
        tRender.addText("<----G A M E  O V E R---->", MIDCENTER, 4.0f);
        score = 0;
    }
}

void State_Game::draw()
{
    Game.Clear();
    tPlayer.draw(Game);
    tEnemies.draw(Game);
    plyBulletFactory.draw(Game);
    tRender.draw(Game);
    tInterface.draw(Game);
    Game.Display();
}
