#include <fstream>

#include "../util/Logger.h"
#include "SpriteManager.h"
#include "SurfaceManager.h"

SpriteManager* SpriteManager::s_Instance = 0;

SpriteManager* SpriteManager::getInstance()
{
    if (s_Instance == 0)
        s_Instance = new SpriteManager();

    return s_Instance;
}

SpriteManager::SpriteManager() {}

bool SpriteManager::loadSpriteFromFile(const std::string& fileName)
{
    Logger::getInstance()->logInfo("At SpriteManager::loadSpriteFromFile.");
    Logger::getInstance()->logInfo("Try load sprite named " + fileName);
    std::ifstream ifs(fileName.c_str());

    if (!ifs)
        return false;

    Logger::getInstance()->logInfo("File stream is good.");
    Sprite* sprite = new Sprite();

    //Logger::getInstance()->logInfo("Call sprite::loadSprite()");

    if (!sprite->loadSprite(ifs))
    {
        //Logger::getInstance()->logError("Sprite loading failed.");
        delete sprite;
        return false;
    }
    Logger::getInstance()->logInfo("Add sprite to vector.");
    m_AllSprites.push_back(sprite);

    //Logger::getInstance()->logInfo("All is Oke");
    return true;
}

bool SpriteManager::loadSpritesFromList(const SpriteList& list)
{
    for (auto it = list.m_Paths.cbegin(); it != list.m_Paths.cend(); ++it)
        if (!loadSpriteFromFile(*it))
            return false;

    return true;
}

Sprite* SpriteManager::getSpriteById(size_t id)
{
    if (id >= m_AllSprites.size())
        return 0;

    return m_AllSprites[id];
}

void SpriteManager::deleteAllSprites()
{
    for (auto it = m_AllSprites.begin(); it != m_AllSprites.end(); ++it)
        delete (*it);

    m_AllSprites.clear();
}

SpriteList::SpriteList (std::string defaultPath) : m_DefaultPath(defaultPath) {}

void SpriteList::setDefaultPath (std::string path)
{
    m_DefaultPath = path;
}

void SpriteList::addSprite (std::string path, std::string name)
{
    m_Paths.push_back(path + name);
}

void SpriteList::addSprite (std::string name)
{
    m_Paths.push_back(m_DefaultPath + name);
}
