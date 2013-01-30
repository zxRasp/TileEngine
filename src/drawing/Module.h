
#ifndef _MODULE_H_
#define _MODULE_H_

#include "../Common.h"

struct Module
{
    PSURFACE    m_pSurface;
    RECT        m_Rect;

    //ctor
    Module(PSURFACE s, int x, int y, int w, int h) : m_pSurface(s)
    {
        m_Rect.x = x;
        m_Rect.y = y;
        m_Rect.w = w;
        m_Rect.h = h;
    }

    Module(PSURFACE s, RECT r) : m_pSurface(s), m_Rect(r) {}
};

#endif // _MODULE_H_
