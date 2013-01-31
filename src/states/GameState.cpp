#include <string>

#include <SDL.h>

#include "../util/Logger.h"
#include "../util/StringUtil.h"
#include "../managers/SurfaceManager.h"
#include "../managers/SpriteManager.h"
#include "../managers/StateManager.h"
#include "../managers/TilemapManager.h"

#include "GameState.h"

GameState::GameState() : m_pPlayer(0), m_playerAction(IDLE), m_frames(0), m_time(0) {}

void GameState::init()
{
    Logger::getInstance()->logInfo("GameState::init()");
    m_pGraphics = new Graphics(SurfaceManager::getInstance()->getCurrScreen());
    RECT viewRect;
    viewRect.x = 0;
    viewRect.y = 0;
    viewRect.w = 800;
    viewRect.h = 600;

    TileMap* currMap = TilemapManager::getInstance()->getTilemapById(0);
    m_WorldSize = currMap->getWidth() * currMap->getTileWidth();
    m_pCamera = new Camera(m_pGraphics, viewRect);
    m_pPlayer = new Player(SpriteManager::getInstance()->getSpriteById(4), 64, 384);
}

void GameState::destroy()
{
    delete m_pPlayer;
    delete m_pCamera;
    delete m_pGraphics;
    Logger::getInstance()->logInfo("GameState::destroy()");
}

void GameState::update(size_t dt)
{
    bool exit = false;
    // message processing loop
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        // check for messages
        switch (event.type)
        {
            case SDL_QUIT:
                exit = true;
                break;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    exit = true;
                else if (event.key.keysym.sym == SDLK_RIGHT)
                    m_playerAction = ActorActions::MOVE_RIGHT;
                else if (event.key.keysym.sym == SDLK_LEFT)
                    m_playerAction = ActorActions::MOVE_LEFT;
                break;

            case SDL_KEYUP:
                if (event.key.keysym.sym == SDLK_LEFT ||
                    event.key.keysym.sym == SDLK_RIGHT)
                    m_playerAction = ActorActions::IDLE;
                break;

        } // end switch
    } // end of message processing

    TilemapManager::getInstance()->getTilemapById(0)->update(dt);
    m_pPlayer->doAction(m_playerAction);
    m_pPlayer->update(dt);

    if (m_playerAction == ActorActions::MOVE_LEFT ||
        m_playerAction == ActorActions::MOVE_RIGHT)
        updateCameraPos();

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
    m_pPlayer->draw(*m_pCamera);
}

void GameState::updateCameraPos()
{
    float playerXPos = m_pPlayer->getBounds().x - m_pPlayer->getBounds().w / 2;

    float newX = std::max(0.0f, playerXPos - m_pCamera->getDrawRect().w / 2);
    newX = std::min(newX, (float) (m_WorldSize - m_pCamera->getDrawRect().w));

    m_pCamera->move(newX, 0);
}
