#include "State.h"
#include "State_StartMenu.h"
#include "State_Game.h"

enum STATE { STATE_STARTMENU, STATE_GAME };

int main(int argc, char** argv)
{
    State* states[2];
    states[0] = new State_StartMenu();
    states[1] = new State_Game();

    int currentState = STATE_STARTMENU;

    while (states[currentState]->isActive()) {
      states[currentState]->handleEvents();
      states[currentState]->think();
      states[currentState]->draw();

      currentState = states[currentState]->nextState;
    }

    delete states[0];
    delete states[1];

    return 0;
}