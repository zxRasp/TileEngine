#include "StateManager.h"

StateManager* StateManager::s_Instance = 0;

StateManager* StateManager::getInstance()
{
    if (s_Instance == 0)
        s_Instance = new StateManager();

    return s_Instance;
}

StateManager::StateManager() : m_newState(0), m_bNeedInit(false), m_bNeedDestroy(false) {}

void StateManager::switchState(IState* state)
{
    m_newState = state;
    m_bNeedInit = true;
    m_bNeedDestroy = true;
}

void StateManager::pushState(IState* state)
{
    m_newState = state;
    m_bNeedInit = true;
    m_bNeedDestroy = false;
}

void StateManager::popState()
{
    m_bNeedInit = false;
    m_bNeedDestroy = true;
}

bool StateManager::update(size_t dt)
{
    if (m_bNeedDestroy)
    {
       IState* st = m_States.top();
       st->destroy();
       delete st;
       m_States.pop();
       m_bNeedDestroy = false;
       return true;
    }

    if (m_newState != 0)
    {
        m_States.push(m_newState);
        m_newState = 0;
        return true;
    }

    if (m_States.empty())
        return false;

    if (m_bNeedInit)
    {
        m_States.top()->init();
        m_bNeedInit = false;
        return true;
    }

    m_States.top()->update(dt);
    m_States.top()->render();

    return true;
}
