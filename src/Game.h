#ifndef _GAME_H_
#define _GAME_H_

#include "states/IState.h"

class Game
{
public:
    Game();
    ~Game();

    void start();

private:
    bool init();
    void run();
    void shutdown();
};

#endif // _GAME_H_
