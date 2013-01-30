#ifndef _TILEMAP_MANAGER_H_
#define _TILEMAP_MANAGER_H_

#include <vector>
#include <string>

#include "../drawing/TileMap.h"

class TilemapManager
{
public:
    static TilemapManager* getInstance();

    void        loadTilemapFromFile  (const std::string& filename);
    TileMap*    getTilemapById       (size_t id);
    void        deleteAllTilemaps    ();

private:
    TilemapManager();

    static TilemapManager* s_Instance;
    std::vector<TileMap*>  m_allTileMaps;
};

#endif // _TILEMAP_MANAGER_H_
