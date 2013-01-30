#include "Tile.h"

void Tile::addSprite(Sprite* sp, int animId, int frameId, int x, int y, int anchor)
{
    SpriteEntry spriteEntry (sp, animId, frameId, x, y, anchor);
    m_RenderingList.push_back(spriteEntry);
}

void Tile::update(size_t dt)
{
    for (auto it = m_RenderingList.cbegin(); it != m_RenderingList.cend(); ++it)
        if ((*it).m_AnimId != -1)
            (*it).m_pSprite->updateAnimation((*it).m_AnimId, dt);
}

void Tile::draw(const Graphics& g, int x, int y) const
{
    for (auto it = m_RenderingList.cbegin(); it != m_RenderingList.cend(); ++it)
    {
        if ((*it).m_AnimId != -1)
        {
            (*it).m_pSprite->drawAnimation(g, (*it).m_AnimId, x + (*it).m_Xpos, y + (*it).m_Ypos, (*it).m_Anchor);
            continue;
        }

        if ((*it).m_FrameId != -1)
            (*it).m_pSprite->drawFrame(g, (*it).m_FrameId, x + (*it).m_Xpos, y + (*it).m_Ypos, (*it).m_Anchor);
    }
}
