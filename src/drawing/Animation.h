#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <vector>
#include "Frame.h"
#include "Graphics.h"

struct FrameEntry
{
    Frame* m_pFrame;
    size_t m_Time;

    FrameEntry(Frame* pFrame, size_t time) : m_pFrame(pFrame), m_Time(time) {}
};

class Animation
{
public:
    Animation();
    void addFrame(Frame* pFrame, size_t time);

    void play(bool loop);
    void pause();
    void stop();

    void update(size_t dt);

    void draw(Graphics g, int x, int y, int anchor = 0);

private:
    bool    m_bPlaying;
    bool    m_bLoop;
    size_t  m_Time;
    size_t  m_CurrFrameIndex;

    std::vector<FrameEntry> m_Frames;
};

#endif // _ANIMATION_H_
