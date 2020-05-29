#ifndef CAR_EXAMPLE_GAME_H
#define CAR_EXAMPLE_GAME_H

#include <iostream>
#include <SDL2/SDL.h>
#if defined(__APPLE__)
#include <SDL2_image/SDL_image.h>
#else
#include <SDL2/SDL_image.h>
#endif //__APPLE__
#if defined(__EMSCRIPTEN__)
#include <emscripten.h>
#define EMSCRIPTEN_FLAG 0;
#else
#define EMSCRIPTEN_FLAG 1;
#endif //__EMSCRIPTEN__

#ifdef __DEBUG__
const bool debugMode = true;
#else
const bool debugMode = false;
#endif

class Game {
protected:
    bool mIsEmscripten;
    bool mIsRunning = false;
    SDL_Window *mWindow;
    static int mWidth, mHeight;
    /**
     * Frame Limiting
     */
    const int mFPS = 60;
    const int mFrameDelay = 1000 / mFPS;
    Uint32 mFrameStart;
    int mFrameTime;
    /**
     * Debug mode
     */
    const bool mIsDebug = debugMode;

public:
    Game();
    ~Game();

    static SDL_Renderer *mRenderer;
    SDL_Event mEvent;

    void Init(const char *title, int xPosition, int yPosition, int width, int height, bool fullscreen);

    void RegisterObjects();

    void WindowResize(int width, int height) {
        SDL_SetWindowSize(mWindow, width, height);
        mWidth = width;
        mHeight = height;
    }

    void HandleEvents();

    void Update();

    void Render();

    void GameLoop();

    void Quit();

    void RenderDrawColor() {
        SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    }

    static std::pair<int, int> GetWindowResolution() {
        int w, h;
        SDL_GetRendererOutputSize(mRenderer, &w, &h);
        if (SDL_GetRendererOutputSize(mRenderer, &w, &h) == 0) {
            //Client window is high dpi device
            return std::make_pair(w, h);
        } else {
            //Unable to get the actual area size in pixels, so the resolution is 1:1
            return std::make_pair(mWidth, mHeight);
        }
    }

    bool isRunning() { return mIsRunning; }
    constexpr bool isEmscripten() { return mIsEmscripten; }
    constexpr bool isDebug() { return mIsDebug; }
};

#endif //CAR_EXAMPLE_GAME_H
