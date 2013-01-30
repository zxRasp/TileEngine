#include "SpriteManager.h"
#include "SurfaceManager.h"
#include "TilemapManager.h"
#include "LoadManager.h"

// LoadList

void LoadList::addLoadItem(ResTypeTag type, const std::string& path)
{
    LoadItem li;
    li.m_Type = type;
    li.m_LoadPath = path;
    m_LoadList.push_back(li);

}

// Load Manager
LoadManager* LoadManager::s_Instance = 0;

LoadManager* LoadManager::getInstance()
{
    if (s_Instance == 0)
        s_Instance = new LoadManager();

    return s_Instance;
}

LoadManager::LoadManager() {}

void LoadManager::setLoadList(LoadList* pList, int startIndex)
{
    m_pList = pList;
    m_CurrItem = startIndex;
}

bool LoadManager::loadProcessing()
{
    if (m_CurrItem >= m_pList->m_LoadList.size())
        return true;

    ResTypeTag type     = m_pList->m_LoadList[m_CurrItem].m_Type;
    std::string path    = m_pList->m_LoadList[m_CurrItem].m_LoadPath;

    switch(type)
    {
        case TAG_SURFACE:
            SurfaceManager::getInstance()->loadSurfaceFromFile(path);
            break;

        case TAG_SPRITE:
            SpriteManager::getInstance()->loadSpriteFromFile(path);
            break;

        case TAG_TILEMAP:
            TilemapManager::getInstance()->loadTilemapFromFile(path);
            break;
    }

    ++m_CurrItem;
    return false;
}
