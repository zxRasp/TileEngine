#ifndef _SPRITE_MANAGER_H_
#define _SPRITE_MANAGER_H_

#include <vector>
#include <string>

#include "../drawing/Sprite.h"

class SpriteList;

class SpriteManager
{
public:
    static SpriteManager* getInstance();

    bool loadSpriteFromFile     (const std::string& fileName);
    bool loadSpritesFromList    (const SpriteList&  list);

    Sprite* getSpriteById       (size_t id);

    void deleteAllSprites();

private:
    SpriteManager();

    std::vector<Sprite*>    m_AllSprites;

    static SpriteManager*   s_Instance;
};

class SpriteList
{
    friend class SpriteManager;
public:
    SpriteList(std::string defaultPath);

    void setDefaultPath (std::string path);
    void addSprite      (std::string path, std::string name);
    void addSprite      (std::string name);

private:
        std::string                 m_DefaultPath;
        std::vector<std::string>    m_Paths;
};

#endif // _SPRITE_MANAGER_H_
