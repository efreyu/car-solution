/* Created by efreyu on 22.05.2020. */
#include <iostream>
#include <cstdlib>
#include <vector>
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

enum eDirection : std::size_t {
    UP, RIGHT, DOWN, LEFT
};

struct sTransform {
public:
    int x, y, width, height;
    eDirection direction;

    sTransform() { x = y = width = height = 0; direction = eDirection::DOWN; }
    sTransform(int transformX, int transformY, int transformWidth, int transformHeight, eDirection transformDirection = eDirection::DOWN)
        : x(transformX)
        , y(transformY)
        , width(transformWidth)
        , height(transformHeight)
        , direction(transformDirection)
        {};
};

class Collision {
public:
    /*
     * Axis-aligned bounding boxes (AABB) are the quickest algorithm
     * to determine whether the two game entities are overlapping or not.
     */
    static bool AABB(const sTransform &transformA, const sTransform &transformB) {
        return transformA.x + transformA.width >= transformB.x &&
               transformB.x + transformB.width >= transformA.x &&
               transformA.y + transformA.height >= transformB.y &&
               transformB.y + transformB.height >= transformA.y;
    }
};

struct sCar {
private:
    int speed;
    int minSpeed = 1;

public:
    sTransform transform;

    sCar() { speed = 0; };
    sCar(int speed, sTransform transform) : speed(speed), transform(transform) {};

    void move() {
        switch (transform.direction) {
            case eDirection::UP:
                transform.y += getSpeed();
                break;
            case eDirection::RIGHT:
                transform.x += getSpeed();
                break;
            case eDirection::DOWN:
                transform.y -= getSpeed();
                break;
            case eDirection::LEFT:
                transform.x -= getSpeed();
                break;
        }
        fuelBurn();
    }

    int getSpeed() { return this->getFuel() > 0 ? speed : minSpeed; };

    void setSpeed(int i) { speed = i; };

    virtual void fuelBurn() = 0;

    virtual int getFuel() = 0;

    virtual void refill(int count) = 0;
};

struct sGasEngine : virtual public sCar {
protected:
    int fuel;

public:
    sGasEngine() : fuel(0) {}

    int getFuel() override { return fuel; }

    void refill(int count) override { fuel += count; }

    void fuelBurn() override {
        if (fuel > 0) fuel--;
    }
};

struct sElectroCar : virtual public sCar {
protected:
    int charge;

public:
    sElectroCar() : charge(0) {};

    int getFuel() override { return charge; }

    void refill(int count) override { charge += count; }

    void fuelBurn() override {
        if (charge > 0) charge--;
    }
};

struct sHybridCar : virtual public sGasEngine, virtual public sElectroCar {
public:
    sHybridCar() {
        sGasEngine();
        sElectroCar();
    }

    void refill(int count) override {
        /* When we pass an odd number we always lose 1, due to int type casting.
         * The solution is to change the int to float for storing fuel, or use a temporary float variable.
         */
        charge += count / 2; fuel += count / 2;
    }

    int getFuel() override { return charge + fuel; }

    void fuelBurn() override {
        if (rand() % 2 == 0)
            sElectroCar::fuelBurn();
        else
            sGasEngine::fuelBurn();
    }
};

class Game {
private:
    bool mIsEmscripten;
    bool mIsRunning = false;
    SDL_Window *mWindow;
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
    static const auto mIsDebug = debugMode;

public:
    SDL_Renderer *mRenderer;
    SDL_Event mEvent;

    Game() {
        mRenderer = nullptr;
    }
    ~Game() = default;

    void Init(const char *title, int xPosition, int yPosition, int width, int height, bool fullscreen)
    {
        int fullscreen_flag = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
        Uint32 render_flag = SDL_RENDERER_ACCELERATED;

        auto emsTemp = EMSCRIPTEN_FLAG;
        mIsEmscripten = emsTemp == 0;

        if((mIsEmscripten && SDL_Init( SDL_INIT_VIDEO ) == 0) || (!mIsEmscripten && SDL_Init(SDL_INIT_EVERYTHING) == 0))
        {
            if( !SDL_SetHint( SDL_HINT_RENDER_VSYNC, "1" ) )
            {
                printf( "Warning: vsync rendering not enabled!" );
            }
            // Initialize SDL.
            mWindow = SDL_CreateWindow(title, xPosition, yPosition, width, height, fullscreen_flag);
            if (!mWindow) {
                std::cout << "Warning: window was not created!" << std::endl;
            }

            mRenderer = SDL_CreateRenderer(mWindow, -1, render_flag);
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

    void WindowResize(int width, int height) {
        SDL_SetWindowSize(mWindow, width, height);
    }

    void HandleEvents()
    {
        SDL_PollEvent(&mEvent);
        switch (mEvent.type) {
            case SDL_QUIT:
                mIsRunning = false;
                break;

            default:
                break;
        }
    }

    void Update() {
        //
    }

    void Render() {
        SDL_RenderClear(mRenderer);
        //
        SDL_RenderPresent(mRenderer);
    }

    void GameLoop()
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

    void Quit()
    {
        SDL_DestroyWindow(mWindow);
        SDL_DestroyRenderer(mRenderer);
        SDL_Quit();
    }

    void RenderDrawColor() {
        SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    }

    bool isRunning() { return mIsRunning; }
    constexpr bool isEmscripten() { return mIsEmscripten; }
    constexpr bool isDebug() { return mIsDebug; }
};