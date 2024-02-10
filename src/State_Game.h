#ifndef STATE_GAME_H_
#define STATE_GAME_H_

#include "BulletFactory.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "Interface.h"
#include "LevelMachine.h"
#include "TextRenderer.h"
#include "Player.h"

// The entire games logic, top view.
class State_Game : public State
{
    private:
        const int screenW;
        const int screenH;
        const int gameW;
        const int gameH;
        int score;

        sf::Clock deltaTimer;

        std::vector<Enemy*> enemies;

        sf::RenderWindow Game;
        Interface tInterface;
        TextRenderer tRender;
        Player tPlayer;
        EnemyManager tEnemies;
        BulletFactory plyBulletFactory;
        LevelMachine tLevels;

    public:
        State_Game();
        void handleEvents();
        void think();
        void draw();
        bool isActive() {return Game.IsOpened();}

        void open();
        void close();
};

#endif // STATE_GAME_H_
