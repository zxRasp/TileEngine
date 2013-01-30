#ifndef _STATE_MANAGER_H_
#define _STATE_MANAGER_H_

#include <stack>

#include "../states/IState.h"

class StateManager
{
public:
    static StateManager* getInstance();

    void switchState (IState* newState);
    void pushState   (IState* newState);
    void popState    ();

    bool update (size_t dt);

private:
    StateManager();

    static StateManager* s_Instance;

    std::stack<IState*> m_States;

    IState* m_newState;

    bool    m_bNeedInit;
    bool    m_bNeedDestroy;
};

#endif // _STATE_MANAGER_H_
