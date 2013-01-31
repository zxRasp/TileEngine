#ifndef _ACTOR_H_
#define _ACTOR_H_

#include "../Common.h"
#include "../drawing/Camera.h"

enum ActorActions
{
    IDLE,
    MOVE_LEFT,
    MOVE_RIGHT
};

class IActor
{
public:

    virtual void        doAction    (ActorActions action) = 0;
    virtual void        update      (size_t dt)           = 0;
    virtual void        draw        (Camera& cam) const   = 0;
    virtual const RECT& getBounds   ()            const   = 0;
};

#endif // _ACTOR_H_
