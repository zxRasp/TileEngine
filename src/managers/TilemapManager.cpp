#include "TilemapManager.h"

TilemapManager* TilemapManager::s_Instance = 0;

TilemapManager* TilemapManager::getInstance()
{
    if (s_Instance == 0)
        s_Instance = new TilemapManager();

    return s_Instance;
}

TilemapManager::TilemapManager() {}

void TilemapManager::loadTilemapFromFile(const std::string& filename)
{
    TileMap* tm = new TileMap();

    tm->loadFromFile(filename);

    m_allTileMaps.push_back(tm);
}

TileMap* TilemapManager::getTilemapById(size_t id)
{
    return m_allTileMaps[id];
}

void TilemapManager::deleteAllTilemaps()
{
    for (auto it = m_allTileMaps.begin(); it != m_allTileMaps.end(); ++it)
        delete (*it);

    m_allTileMaps.clear();
}
