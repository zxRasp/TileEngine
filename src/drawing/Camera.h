#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "../Common.h"
#include "Graphics.h"

class Camera
{
public:
    Camera(Graphics* g, RECT drawRect) : m_pGraphics(g), m_DrawRect(drawRect) {}

    Graphics*   getGraphics() const { return m_pGraphics; }
    RECT        getDrawRect() const { return m_DrawRect; }

    void        move(int x, int y) { m_DrawRect.x = x, m_DrawRect.y = y; }

private:
    Graphics* m_pGraphics;
    RECT      m_DrawRect;
};

#endif // _CAMERA_H_
