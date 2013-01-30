#ifndef _SURFACEMANAGER_H_
#define _SURFACEMANAGER_H_

#include <string>
#include <vector>

#include "../Common.h"

class SurfaceManager
{
public:
    static SurfaceManager* getInstance();

    PSURFACE loadSurfaceFromFile    (std::string filename);
    PSURFACE createSurfaceCopy      (PSURFACE original, int newWidth = 0, int newHeight = 0);
    PSURFACE getSurfaceById         (size_t id);

    void        setCurrScreen (PSURFACE screen);
    PSURFACE    getCurrScreen ();

    void freeAllSurfaces();

private:
    SurfaceManager();

    static SurfaceManager*  s_Instance;

    std::vector<PSURFACE>   m_AllSurfaces;

    PSURFACE                m_Screen;
};

#endif // _SURFACEMANAGER_H_
