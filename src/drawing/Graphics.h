#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include "../Common.h"
#include "Module.h"

class Graphics
{
public:
    // ctor
    Graphics(PSURFACE pCanvasSurfase);

    // draw methods
    void drawModule (Module& m, int x, int y, bool isDebug = false);
    void drawLine   (int x1, int y1, int x2, int y2, Uint32 color);
    void drawRect   (const RECT& rect, Uint32 color);

    // clipping
    void getClipRect (RECT* clip);
    void setClipRect (RECT* clip);

    // general purpose static methods
    static Uint32   getPixel32 (PSURFACE surface, int x, int y);
    static void     putPixel32 (PSURFACE surface, int x, int y, Uint32 pixel);
    static void     FlipModule (Module&  module,  bool flipHorizontal, bool flipVertical);

private:
    PSURFACE m_pCanvasSurface;
};

#endif // _GRAPHICS_H_
