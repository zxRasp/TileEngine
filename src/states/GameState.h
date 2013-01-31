#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include "IState.h"
#include "../drawing/Camera.h"

class GameState : public IState
{
public:
    GameState();

    void init();
    void destroy();
    void update(size_t dt);
    void render();

    virtual ~GameState() {};

private:
    Graphics*   m_pGraphics;
    Camera*     m_pCamera;

    int         m_frames;
    size_t      m_time;
};

#endif // _GAME_STATE_H_
