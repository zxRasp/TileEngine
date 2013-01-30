#include <SDL.h>
#include <SDL_gfxPrimitives.h>

#include "Graphics.h"
#include "../managers/SurfaceManager.h"

Graphics::Graphics(PSURFACE pCanvasSurfase) : m_pCanvasSurface(pCanvasSurfase) {}

void Graphics::drawModule(Module& module, int x, int y, bool isDebug)
{
    RECT dstRect;
    dstRect.x = x;
    dstRect.y = y;

    SDL_BlitSurface(module.m_pSurface, &module.m_Rect, m_pCanvasSurface, &dstRect);

    if (isDebug)
    {
        RECT rc;
        rc.x = x;
        rc.y = y;
        rc.w = module.m_Rect.w;
        rc.h = module.m_Rect.h;
        drawRect(rc, 0x00FF00FF); // RGBA color format
    }
}

void Graphics::drawLine (int x1, int y1, int x2, int y2, Uint32 color)
{
    lineColor(m_pCanvasSurface, x1, y1, x2, y2, color);
}

void Graphics::drawRect (const RECT& rect, Uint32 color)
{
    rectangleColor(m_pCanvasSurface, rect.x, rect.y, rect.x + rect.w, rect.y + rect.h, color);
}

void Graphics::getClipRect (RECT* clip)
{
    SDL_GetClipRect(m_pCanvasSurface, clip);
}

void Graphics::setClipRect (RECT* clip)
{
    SDL_SetClipRect(m_pCanvasSurface, clip);
}

Uint32 Graphics::getPixel32 (PSURFACE surface, int x, int y)
{
    Uint32* pixels = (Uint32*) surface->pixels;

    return pixels[(y * surface->w) + x];
}

void Graphics::putPixel32 (PSURFACE surface, int x, int y, Uint32 pixel)
{
    Uint32* pixels = (Uint32*) surface->pixels;

    pixels[(y * surface->w) + x] = pixel;
}

void  Graphics::FlipModule (Module& module, bool flipHorizontal, bool flipVertical)
{
    PSURFACE newSurf = SurfaceManager::getInstance()->createSurfaceCopy(module.m_pSurface, module.m_Rect.w, module.m_Rect.h);

    if (SDL_MUSTLOCK(newSurf))
        SDL_LockSurface(newSurf);

    for (int originalX = module.m_Rect.x, newX =  0, newRX = module.m_Rect.w - 1;
         newX < module.m_Rect.w;
         originalX++, newX++, newRX--)

        for (int originalY = module.m_Rect.y, newY = 0, newRY = module.m_Rect.h - 1;
             newY < module.m_Rect.h;
             originalY++, newY++, newRY--)
            {
                Uint32 pixel = getPixel32(module.m_pSurface, originalX, originalY);
                putPixel32(newSurf, flipHorizontal ? newRX : newX, flipVertical ? newRY : newY, pixel);
            }

    if (SDL_MUSTLOCK(newSurf))
        SDL_UnlockSurface(newSurf);

    if (module.m_pSurface->flags & SDL_SRCCOLORKEY)
        SDL_SetColorKey(newSurf, SDL_RLEACCEL | SDL_SRCCOLORKEY, module.m_pSurface->format->colorkey);

    module.m_pSurface = newSurf;
    module.m_Rect.x = 0;
    module.m_Rect.y = 0;
}
