/* Created by efreyu on 24.05.2020. */

#include "Game.h"
#include "Manager.h"
#include "MapManager.h"
#include <vector>

auto manager = new Manager;
auto mapManager = new MapManager;
bool buttonPressed = false;
/*
 * Define static
 */
bool Game::mIsEmscripten = false;
SDL_Renderer* Game::mRenderer = nullptr;
int Game::mWidth = 0;
int Game::mHeight = 0;

Game::Game() {}

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
        mWidth = width;
        mHeight = height;
        mIsRunning = true;
        RegisterObjects();
    } else {
        mIsRunning = false;
    }

}

void Game::RegisterObjects() {
    manager = new Manager;
    manager->RegisterCarType<GasEngineCreator>((std::vector<std::string>){
            "resources/sprites/Gas/grey.png",
            "resources/sprites/Gas/red.png",
            "resources/sprites/Gas/white.png"
    });
    manager->RegisterCarType<ElectroCarCreator>((std::vector<std::string>){
            "resources/sprites/Electro/black.png",
            "resources/sprites/Electro/blue.png",
            "resources/sprites/Electro/red.png",
            "resources/sprites/Electro/yellow.png"
    });
    manager->RegisterCarType<HybridCarCreator>((std::vector<std::string>){
            "resources/sprites/Hybrid/black.png",
            "resources/sprites/Hybrid/grey.png",
            "resources/sprites/Hybrid/white.png"
    });
    manager->SpawnCar(10);

    //fill the ground texture
    mapManager = new MapManager;
    mapManager->InitRoadTexture("resources/sprites/road/road_line.png", 256, 256);
    mapManager->InitCrossroadTexture("resources/sprites/road/road_cross.png", 256, 256);
}

void Game::HandleEvents() {
    SDL_PollEvent(&mEvent);
    switch (mEvent.type) {
        case SDL_QUIT:
            mIsRunning = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (!buttonPressed) buttonPressed = true;
            break;
        case SDL_MOUSEBUTTONUP:
            if (buttonPressed) {
                manager->SpawnCar(5);
                buttonPressed = !buttonPressed;
            }
            break;
        default:
            break;
    }
}

void Game::Update() {
    mapManager->Update();
    manager->Update();
}

void Game::Render() {
    SDL_RenderClear(mRenderer);
    mapManager->Draw();
    manager->Draw();
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