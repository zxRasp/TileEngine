#include <iostream>
#include "Animation.h"

Animation::Animation() : m_bPlaying(false), m_bLoop(false), m_Time(0), m_CurrFrameIndex(0) {}

void Animation::addFrame (Frame* pFrame, size_t time)
{
    FrameEntry fe(pFrame, time);
    m_Frames.push_back(fe);
}

void Animation::play(bool loop)
{
    m_bLoop = loop;
    m_bPlaying = true;
}

void Animation::pause()
{
    m_bPlaying = false;
}

void Animation::stop()
{
    m_bPlaying = false;
    m_CurrFrameIndex = 0;
    m_Time = 0;
}

void Animation::update(size_t dt)
{
    if (!m_bPlaying)
        return;

    m_Time += dt;

    if (m_Time >= m_Frames[m_CurrFrameIndex].m_Time)
    {
        m_Time = 0;
        ++m_CurrFrameIndex;
        if (m_CurrFrameIndex >= m_Frames.size())
        {
            m_CurrFrameIndex = 0;
            m_bPlaying = m_bLoop;
        }
    }
}

void Animation::draw(Graphics g, int x, int y, int anchor)
{
    m_Frames[m_CurrFrameIndex].m_pFrame->draw(g, x, y, anchor);
}
