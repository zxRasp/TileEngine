#include "../util/Logger.h"
#include "Sprite.h"
#include "../managers/SurfaceManager.h"

// draw routines
void Sprite::drawFrame (Graphics g, size_t frameId, int x, int y, int anchor)
{
    m_Frames[frameId].draw(g, x, y, anchor);
}

void Sprite::drawAnimation (Graphics g, size_t animId,  int x, int y, int anchor)
{
    m_Animations[animId].draw(g, x, y, anchor);
}

// animations control

void Sprite::playAnimation (size_t animId, bool loop)
{
    m_Animations[animId].play(loop);
}

void Sprite::pauseAnimation (size_t animId)
{
    m_Animations[animId].pause();
}

void Sprite::stopAnimation  (size_t animId)
{
    m_Animations[animId].stop();
}

void Sprite::updateAnimation(size_t animId, size_t dt)
{
    m_Animations[animId].update(dt);
}

// getters
const Frame& Sprite::getFrame (size_t frameId) const
{
    return m_Frames[frameId];
}

const Animation& Sprite::getAnimation (size_t animId) const
{
    return m_Animations[animId];
}

// loading sprite data

/*
    Load sprite from data stream.
    Stream format:
    int version  - version of sprite;
    int nModules - count of modules
    /.../        - data of each module
    int nFrames  - count of frames
    /.../        - data of each frame
    int nAnims   - count of Animations (only if nFrames > 0)
    /.../        - data of each animation
*/
bool Sprite::loadSprite(std::istream& is)
{
    Logger::getInstance()->logInfo("At Sprite::loadSprite()");
    int version;
    is >> version;

    //Logger::getInstance()->logInfo("Check version");
    if (version > CURR_VERSION)
        return false;

    int nModules;
    is >> nModules;

    //Logger::getInstance()->logInfo("Check Modules");
    if (nModules < 1)
        return false;

  //  Logger::getInstance()->logInfo("Try load modules");
    if (!loadModules(is, nModules))
        return false;

    //Logger::getInstance()->logInfo("Check frames");
    int nFrames;
    is >> nFrames;

    if (nFrames > 0)
    {
       // Logger::getInstance()->logInfo("Try load frames");
        if (!loadFrames(is, nFrames))
            return false;

       // Logger::getInstance()->logInfo("Check animations");
        int nAnimations;
        is >> nAnimations;

       // Logger::getInstance()->logInfo("Try load animations");
        if (nAnimations > 0 && !loadAnimations(is, nAnimations))
            return false;

        return true;
    }

    return true;
}

/*
    Load modules data.
    Format:
    a) for original modules:
    * surface_id (always >= 0), x, y, w, h
    b) for flipped modules:
    * -1, original_module_id, is_h_flip, is_v_flip
*/

bool Sprite::loadModules(std::istream& is, int modulesCount)
{
    Logger::getInstance()->logInfo("Load modules");

    for (int i = 0; i < modulesCount; ++i)
    {
        int surfaceIndex;
        is >> surfaceIndex;
        if (surfaceIndex < 0)
        {
            size_t originalModuleIndex;
            is >> originalModuleIndex;
            Module m = m_Modules[originalModuleIndex];

            bool flipH, flipV;
            is >> flipH >> flipV;
            Graphics::FlipModule(m, flipH, flipV);
            m_Modules.push_back(m);
        }
        else
        {
            int x, y, w, h;
            is >> x >> y >> w >> h;
            m_Modules.push_back(Module(SurfaceManager::getInstance()->getSurfaceById(surfaceIndex), x, y, w, h));
        }
    }
     Logger::getInstance()->logInfo("Modules was loaded");
    return true;
}

/*
    Load frames data;
    Format:
    width, height,
    modules_count,
    module_id, x, y // for each module in frame
*/
bool Sprite::loadFrames (std::istream& is, int framesCount)
{
    //Logger::getInstance()->logInfo("Load frames");
    for (int i = 0; i < framesCount; ++i)
    {
        int w, h;
        is >> w >> h;
        Frame f(w, h);

        int nModules;
        is >> nModules;
        for (int j = 0; j < nModules; ++j)
        {
            int id, x, y;
            is >> id >> x >> y;
            f.addModule(&m_Modules[id], x, y);
        }

        m_Frames.push_back(f);
        //Logger::getInstance()->logDebug("frame loaded...");
    }
    //Logger::getInstance()->logInfo("Frames was loaded");
    return true;
}

/*
    Load animations data;
    Format:
    frame_count,
    frame_id, time // for each frame
*/
bool Sprite::loadAnimations (std::istream& is, int animationsCount)
{
    for (int i = 0; i < animationsCount; ++i)
    {
        int frameCount;
        is >> frameCount;

        Animation anim;

        for(int j = 0; j < frameCount; ++j)
        {
            int frameId, time;
            is >> frameId >> time;
            anim.addFrame(&m_Frames[frameId], time);
        }
        m_Animations.push_back(anim);
    }
    return true;
}
