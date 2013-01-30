#ifndef _LOAD_STATE_H_
#define _LOAD_STATE_H_

#include "IState.h"
#include "../managers/LoadManager.h"

class LoadState : public IState
{
public:
    void init();
    void destroy();
    void update(size_t dt);
    void render();
private:
    LoadList* m_pLoadList;
};

#endif // _LOAD_STATE_H_
