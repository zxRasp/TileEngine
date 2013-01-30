#ifndef _ISTATE_H_
#define _ISTATE_H_

#include <cstdlib>

class IState
{
public:
    virtual void init()             = 0;
    virtual void destroy()          = 0;
    virtual void update(size_t dt)  = 0;
    virtual void render()           = 0;

    virtual ~IState() {};
};

#endif // _ISTATE_H_
