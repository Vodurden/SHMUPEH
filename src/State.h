#ifndef STATE_H_
#define STATE_H_

// Base class for all types of states (Windows open on the game)
class State
{
    protected:
        int nextState;
    public:
        State() {nextState = 0;}
        virtual ~State() {}
        virtual void handleEvents();
        virtual void think();
        virtual void draw();
        virtual void open() {}
        virtual void close() {}
        virtual bool isActive();
        int getNextState() {return nextState;}
};

#endif // STATE_H_
