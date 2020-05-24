/* Created by efreyu on 24.05.2020. */

#include "Game.h"

SDL_Renderer* Game::mRenderer = nullptr;

Game::Game() {
    mManager = new Manager();
    auto *gasEngine = new GasEngineCreator();
    mManager->addCarType<Creator>();
}
Game::~Game() {}

void Game::Init(const char *title, int xPosition, int yPosition, int width, int height, bool fullscreen) {
    int fullscreenFlag = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
    Uint32 renderFlag = SDL_RENDERER_ACCELERATED;

    auto emsTemp = EMSCRIPTEN_FLAG;
    mIsEmscripten = emsTemp == 0;

    if((mIsEmscripten && SDL_Init( SDL_INIT_VIDEO ) == 0) || (!mIsEmscripten && SDL_Init(SDL_INIT_EVERYTHING) == 0))
    {
        if( !SDL_SetHint( SDL_HINT_RENDER_VSYNC, "1" ) )
        {
            printf( "Warning: vsync rendering not enabled!" );
        }
        // Initialize SDL.
        mWindow = SDL_CreateWindow(title, xPosition, yPosition, width, height, fullscreenFlag);
        if (!mWindow) {
            std::cout << "Warning: window was not created!" << std::endl;
        }

        mRenderer = SDL_CreateRenderer(mWindow, -1, renderFlag);
        if (mRenderer)
        {
            RenderDrawColor();
            SDL_RenderClear(mRenderer);
        } else {
            std::cout << "Warning: renderer was not created!" << std::endl;
        }
        mIsRunning = true;
    } else {
        mIsRunning = false;
    }

}

void Game::HandleEvents() {
    SDL_PollEvent(&mEvent);
    switch (mEvent.type) {
        case SDL_QUIT:
            mIsRunning = false;
            break;

        default:
            break;
    }
}

void Game::Update() {}

void Game::Render() {
    SDL_RenderClear(mRenderer);
    //
    SDL_RenderPresent(mRenderer);
}

void Game::GameLoop()
{
    mFrameStart = SDL_GetTicks();

    HandleEvents();
    Update();
    Render();

    mFrameTime = SDL_GetTicks() - mFrameStart;
    if (mFrameDelay > mFrameTime) {
        SDL_Delay(mFrameDelay - mFrameTime);
    }
}

void Game::Quit()
{
    SDL_DestroyWindow(mWindow);
    SDL_DestroyRenderer(mRenderer);
    SDL_Quit();
}