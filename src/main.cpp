#include "State.h"
#include "State_StartMenu.h"
#include "State_Game.h"
#include "Logger.h"

int main(int argc, char** argv)
{
    Logger::setLogLevel(LOGTYPE_EVENT);
    Logger::setLogFile("shmupeh.log");

    ResourceManager::loadImage("StartImage", "Graphics/startimage.png");
    ResourceManager::loadImage("Interface_Background", "Graphics/interface_background.png");
    // ResourceManager::loadImage("ScoreNode", "Graphics/score_node.png");
    ResourceManager::loadImage("HealthSegment", "Graphics/health_segment.png");
    ResourceManager::loadImage("ShieldSegment", "Graphics/shield_segment.png");
    ResourceManager::loadImage("SelectionBase", "Graphics/selection_base.png");
    ResourceManager::loadImage("Button_Active", "Graphics/button_active.png");
    ResourceManager::loadImage("Button_Pressed", "Graphics/button_pressed.png");
    ResourceManager::loadImage("Button_Unpressed", "Graphics/button_unpressed.png");

    ResourceManager::loadAnimation("Player", "Graphics/player.png", 46, 51, 0.2, 1, false);
    ResourceManager::loadAnimation("Rapid_Bullet", "Graphics/rapid_bullet.png", 12, 28, 0.2, 1, false);
    ResourceManager::loadAnimation("YellowOrb", "Graphics/energy_orb.png", 12, 28, 0.2, 1, false);
    ResourceManager::loadAnimation("Explosion", "Graphics/explosion.png", 80, 80, 0.3, 3, false);

    // Animations -- SHip Placerholers
    ResourceManager::loadAnimation("Rusty", "Graphics/rusty.png", 43, 42, 0.1, 1, false);
    ResourceManager::loadAnimation("Purple_Fighter", "Graphics/rusty.png", 43, 42, 0.1, 1, false);
    ResourceManager::loadAnimation("Green_Fighter", "Graphics/rusty.png", 43, 42, 0.1, 1, false);
    ResourceManager::loadAnimation("Insect", "Graphics/rusty.png", 43, 42, 0.1, 1, false);
    ResourceManager::loadAnimation("Vampire", "Graphics/rusty.png", 43, 42, 0.1, 1, false);
    ResourceManager::loadAnimation("Blaster", "Graphics/rusty.png", 43, 42, 0.1, 1, false);

    // Animationns -- Enemy weapon placeholders
    ResourceManager::loadAnimation("BlueOrb", "Graphics/energy_orb.png", 12, 28, 0.2, 1, false);
    ResourceManager::loadAnimation("EnemyRapidBullet", "Graphics/rapid_bullet.png", 12, 28, 0.2, 1, false);
    ResourceManager::loadAnimation("HawkBullet", "Graphics/rapid_bullet.png", 12, 28, 0.2, 1, false);
    ResourceManager::loadAnimation("Redarang", "Graphics/rapid_bullet.png", 12, 28, 0.2, 1, false);
    ResourceManager::loadAnimation("Lazer", "Graphics/rapid_bullet.png", 12, 28, 0.2, 1, false);

    State* states[2];
    states[0] = new State_StartMenu();
    states[1] = new State_Game();

    int currentState = STATE_STARTMENU;

    while (states[currentState]->isActive()) {
      states[currentState]->handleEvents();
      states[currentState]->think();
      states[currentState]->draw();

      currentState = states[currentState]->getNextState();
    }

    delete states[0];
    delete states[1];

    return 0;
}
