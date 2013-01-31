#ifndef _TILE_MAP_H_
#define _TILE_MAP_H_

#include <vector>
#include <string>

#include "Camera.h"
#include "Tile.h"

class TileMap
{
public:
    const static int CURR_VERSION = 1;

    bool loadFromFile   (const std::string& fileName);
    void update         (size_t dt);
    void renderTo       (const Camera& cam);

    //getters

    size_t getWidth()  const;
    size_t getHeight() const;

    size_t getTileWidth()  const;
    size_t getTileHeight() const;

private:
    std::vector<Tile> m_Tiles;

    size_t  m_Width;
    size_t  m_Height;

    size_t  m_TileW;
    size_t  m_TileH;
};

#endif // _TILE_MAP_H_
