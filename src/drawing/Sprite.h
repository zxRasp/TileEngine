#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <vector>
#include <istream>

#include "Module.h"
#include "Frame.h"
#include "Animation.h"
#include "Graphics.h"

class Sprite
{
public:
    const static int CURR_VERSION = 1;
    // loading
    bool loadSprite(std::istream& is);

    // animation control
    void playAnimation  (size_t animId, bool loop);
    void pauseAnimation (size_t animId);
    void stopAnimation  (size_t animId);
    void updateAnimation(size_t animId, size_t dt);

    // getters
    const Frame&        getFrame     (size_t frameId) const;
    const Animation&    getAnimation (size_t animId)  const;

    // draw
    void drawFrame      (Graphics g, size_t frameId, int x, int y, int anchor = 0);
    void drawAnimation  (Graphics g, size_t animId,  int x, int y, int anchor = 0);

private:
    std::vector<Module>     m_Modules;
    std::vector<Frame>      m_Frames;
    std::vector<Animation>  m_Animations;

    // util functions
    bool loadModules    (std::istream& is, int modulesCount);
    bool loadFrames     (std::istream& is, int framesCount);
    bool loadAnimations (std::istream& is, int animationsCount);
};

#endif //_SPRITE_H_
