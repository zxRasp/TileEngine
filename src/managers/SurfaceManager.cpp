#include <algorithm>
#include <SDL_image.h>
#include "SurfaceManager.h"

SurfaceManager* SurfaceManager::s_Instance = 0;

SurfaceManager* SurfaceManager::getInstance()
{
    if (s_Instance == 0)
        s_Instance = new SurfaceManager();

    return s_Instance;
}

SurfaceManager::SurfaceManager() : m_Screen(0) {}

PSURFACE SurfaceManager::loadSurfaceFromFile(std::string filename)
{
    PSURFACE tmp = IMG_Load(filename.c_str());

    if (tmp)
    {
        PSURFACE result = SDL_DisplayFormat(tmp);
        SDL_FreeSurface(tmp);
        m_AllSurfaces.push_back(result);
        return result;
    }

    return 0;
}

PSURFACE SurfaceManager::createSurfaceCopy (PSURFACE original, int newWidth, int newHeight)
{
    PSURFACE result = SDL_CreateRGBSurface(
                        SDL_SWSURFACE,
                        newWidth  == 0 ? original->w : newWidth,
                        newHeight == 0 ? original->h : newHeight,
                        original->format->BitsPerPixel,
                        original->format->Rmask,
                        original->format->Gmask,
                        original->format->Bmask,
                        (original->flags & SDL_SRCCOLORKEY) ? 0 : original->format->Amask);


    m_AllSurfaces.push_back(result);
    return result;
}

PSURFACE SurfaceManager::getSurfaceById(size_t id)
{
    if (id >= m_AllSurfaces.size())
        return 0;

    return m_AllSurfaces[id];
}

void SurfaceManager::setCurrScreen(PSURFACE screen)
{
    m_Screen = screen;
}

PSURFACE SurfaceManager::getCurrScreen()
{
    return m_Screen;
}

void SurfaceManager::freeAllSurfaces()
{
    std::for_each (m_AllSurfaces.begin(), m_AllSurfaces.end(), SDL_FreeSurface);
}
