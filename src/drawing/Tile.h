#ifndef _TILE_H_
#define _TILE_H_

#include <vector>
#include "Graphics.h"
#include "Sprite.h"

struct SpriteEntry
{
    Sprite* m_pSprite;
    int     m_AnimId;
    int     m_FrameId;
    int     m_Xpos;
    int     m_Ypos;
    int     m_Anchor;

    SpriteEntry(Sprite* sp, int animId, int frameId, int x, int y, int anchor)
        : m_pSprite(sp), m_AnimId(animId), m_FrameId(frameId), m_Xpos(x), m_Ypos(y), m_Anchor(anchor) {}
};

class Tile
{
public:
    void addSprite  (Sprite* sp, int animId, int frameId, int x, int y, int anchor);
    void update     (size_t dt);
    void draw       (const Graphics& g, int x, int y) const;

private:
    std::vector<SpriteEntry> m_RenderingList;
};

#endif // _TILE_H_
