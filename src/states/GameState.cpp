#include <string>

#include <SDL.h>

#include "../util/Logger.h"
#include "../util/StringUtil.h"
#include "../managers/SurfaceManager.h"
#include "../managers/StateManager.h"
#include "../managers/TilemapManager.h"

#include "GameState.h"

GameState::GameState() : m_frames(0), m_time(0) {}

void GameState::init()
{
    Logger::getInstance()->logInfo("GameState::init()");
    m_pGraphics = new Graphics(SurfaceManager::getInstance()->getCurrScreen());
    RECT viewRect;
    viewRect.x = 0;
    viewRect.y = 0;
    viewRect.w = 800;
    viewRect.h = 600;
    m_pCamera = new Camera(m_pGraphics, viewRect);
}

void GameState::destroy()
{
    delete m_pCamera;
    delete m_pGraphics;
    Logger::getInstance()->logInfo("GameState::destroy()");
}

void GameState::update(size_t dt)
{
    bool exit = false;
    int velocityX = 0;
    // message processing loop
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        // check for messages
        switch (event.type)
        {
            // exit if the window is closed
            case SDL_QUIT:
                exit = true;
                break;

                // check for keypresses
            case SDL_KEYDOWN:
                // exit if ESCAPE is pressed
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    exit = true;
                else if (event.key.keysym.sym == SDLK_RIGHT)
                    velocityX += 1;
                else if (event.key.keysym.sym == SDLK_LEFT)
                    velocityX -= 1;
                break;

        } // end switch
    } // end of message processing

    ++m_frames;
    m_time += dt;

    if (m_time >= 1000)
    {
        std::string fps("FPS: ");
        fps += convertToString(m_frames * 1000 / m_time);

        SDL_WM_SetCaption(fps.c_str(), 0);
        m_time = 0;
        m_frames = 0;
    }


    if (exit)
        StateManager::getInstance()->popState();
}

void GameState::render()
{
    TilemapManager::getInstance()->getTilemapById(0)->renderTo(*m_pCamera);
}
