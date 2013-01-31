#include <sstream>

#include "Common.h"
#include "util/Logger.h"
#include "managers/SurfaceManager.h"
#include "managers/SpriteManager.h"
#include "managers/StateManager.h"
#include "states/LoadState.h"
#include "Game.h"

Game::Game() {}

Game::~Game() {}

void Game::start()
{
    if (init())
    {
        run();
        shutdown();
    }
}

bool Game::init()
{
    Logger::getInstance()->logInfo("Game::init()");

    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        Logger::getInstance()->logError("Unable to init SDL:");
        Logger::getInstance()->logError( SDL_GetError() );
        return false;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    PSURFACE screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    if (!screen)
    {
        Logger::getInstance()->logError("Unable to set video mode:");
        Logger::getInstance()->logError( SDL_GetError() );
        return false;
    }

    SurfaceManager::getInstance()->setCurrScreen(screen);

    StateManager::getInstance()->pushState(new LoadState());
    return true;
}

void Game::run()
{
    // program main loop
    Logger::getInstance()->logInfo("Enter to main loop");

    bool running = true;
    size_t prevFrameTime = SDL_GetTicks();

    while (running)
    {
        size_t currFrameTime = SDL_GetTicks();
        running = StateManager::getInstance()->update(currFrameTime - prevFrameTime);
        SDL_Flip(SurfaceManager::getInstance()->getCurrScreen());
        prevFrameTime = currFrameTime;
    }
    // end main loop
}

void Game::shutdown()
{
    SpriteManager::getInstance()->deleteAllSprites();
    SurfaceManager::getInstance()->freeAllSurfaces();

    Logger::getInstance()->logInfo("Exited cleanly.");
    Logger::getInstance()->Shutdown();
}
