#include "Frame.h"

Frame::Frame(int width, int height) : m_Width(width), m_Height(height) {}

void Frame::addModule(Module* m, int x, int y)
{
    ModuleEntry me(m, x, y);
    m_ModulesEnties.push_back(me);
}

void Frame::draw(Graphics& g, int x, int y, int anchor, bool isDebug)
{
    int dx = x;
    if (anchor & Anchor::HCENTER)
        dx = x - m_Width / 2;
    else if (anchor & Anchor::RIGHT)
        dx = x - m_Width;

    int dy = y;
    if (anchor & Anchor::VCENTER)
        dy = y - m_Height / 2;
    else if (anchor & Anchor::BOTTOM)
        dy = y - m_Height;

    RECT oldClip;
    g.getClipRect(&oldClip);

    RECT FrameClip;
    FrameClip.x = dx;
    FrameClip.y = dy;
    FrameClip.w = m_Width;
    FrameClip.h = m_Height;
    g.setClipRect(&FrameClip);

    for (auto it = m_ModulesEnties.begin(); it != m_ModulesEnties.end(); ++it)
        g.drawModule(*(*it).m, dx + (*it).x, dy + (*it).y, isDebug);

    g.setClipRect(&oldClip);

    if (isDebug)
    {
        g.drawRect(FrameClip, 0xFF0088FF);
        g.drawLine(x - 4, y - 4, x + 4, y + 4, 0xFF0088FF);
        g.drawLine(x + 4, y - 4, x - 4, y + 4, 0xFF0088FF);
    }

}
