#ifndef CAR_EXAMPLE_GAME_H
#define CAR_EXAMPLE_GAME_H

#include <iostream>
#include <tuple>
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
    static bool mIsEmscripten;
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
        RegisterObjects(); //Reinit all objects after resizing the canvas
    }

    void HandleEvents();

    void Update();

    void Render();

    void GameLoop();

    void Quit();

    void RenderDrawColor() {
        SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    }

    static std::tuple<int, int, float> GetWindowResolution() {
        int w, h;
        if (!mIsEmscripten && SDL_GetRendererOutputSize(mRenderer, &w, &h) == 0) {
            //Client window is high dpi device
            return std::make_tuple(w, h, std::abs(w / mWidth));
        } else {
            //Unable to get the actual area size in pixels, so the resolution is 1:1
            return std::make_tuple(mWidth, mHeight, 1);
        }
    }

    bool isRunning() { return mIsRunning; }
    static bool isEmscripten() { return mIsEmscripten; }
    constexpr bool isDebug() { return mIsDebug; }
};

#endif //CAR_EXAMPLE_GAME_H
