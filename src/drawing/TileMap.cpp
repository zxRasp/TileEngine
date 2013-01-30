#include <fstream>
#include "TileMap.h"
#include "../managers/SpriteManager.h"
#include "../util/Collisions.h"
#include "../util/Logger.h"

bool TileMap::loadFromFile(const std::string& fileName)
{
    Logger::getInstance()->logInfo("TileMap:load from file");
    Logger::getInstance()->logInfo(fileName);

    std::ifstream ifs(fileName.c_str());

    if (!ifs)
        return false;

    Logger::getInstance()->logInfo("fstream is ok");
    int version;
    ifs >> version;

    if (version > CURR_VERSION)
        return false;

    Logger::getInstance()->logInfo("version is ok");

    ifs >> m_TileW;
    ifs >> m_TileH;
    ifs >> m_Width;
    ifs >> m_Height;

    int tilesCount = m_Width * m_Height;

    for (int i = 0; i < tilesCount; ++i)
    {
        Tile tile;
        int spriteId, animId, frameId, x, y, anchor;
        ifs >> spriteId >> animId >> frameId >> x >> y >> anchor;
        Sprite* sp = SpriteManager::getInstance()->getSpriteById(spriteId);

        if (!sp)
        {
            Logger::getInstance()->logError("Invalid sprite in tileset!");
            return false;
        }


        tile.addSprite(sp, animId, frameId, x, y, anchor);
        m_Tiles.push_back(tile);
    }

    Logger::getInstance()->logInfo("Tileset loaded");
    return true;
}

void TileMap::update(size_t dt)
{
    for (auto it = m_Tiles.begin(); it != m_Tiles.end(); ++it)
    {
        (*it).update(dt);
    }
}

void TileMap::renderTo(const Camera& cam)
{
    int tileNumber = 0;
    RECT tileRect;
    tileRect.w = m_TileW;
    tileRect.h = m_TileH;

    for (auto it = m_Tiles.cbegin(); it != m_Tiles.cend(); ++it)
    {
        int tilePosX = tileNumber % m_Width;
        int tilePosY = tileNumber / m_Width;

        tileRect.x = tilePosX * m_TileW;
        tileRect.y = tilePosY * m_TileH;

        if (isRectIntersect(tileRect, cam.getDrawRect()))
            (*it).draw(*(cam.getGraphics()), tileRect.x - cam.getDrawRect().x, tileRect.y - cam.getDrawRect().y);

        ++tileNumber;
    }
}
