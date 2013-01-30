#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include "IState.h"
#include "../drawing/Camera.h"

class GameState : public IState
{
    void init();
    void destroy();
    void update(size_t dt);
    void render();

    virtual ~GameState() {};

private:
    Graphics*   m_pGraphics;
    Camera*     m_pCamera;
};

#endif // _GAME_STATE_H_
