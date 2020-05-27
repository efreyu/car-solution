#ifndef CAR_EXAMPLE_SCARS_H
#define CAR_EXAMPLE_SCARS_H


#include "Transform.h"

//#include "LoadManager.h"

struct sCar {
private:
    int speed;
    int minSpeed = 1;

public:
    sTransform transform;
    SDL_Texture *texture{};
    SDL_Rect srcRect{}, destRect{};

    sCar() { speed = 0; };
    sCar(int speed, sTransform transform) : speed(speed), transform(transform) {};
    ~sCar() {
        SDL_DestroyTexture(texture);
    }

    void loadTexture(std::string path) {
        const char* c = path.c_str();
//        auto *load = new LoadManager();
//        texture = LoadManager::LoadTexture(c/*(const char*)path.c_str()*/);

    }

    void draw() {
//        LoadManager::Draw(texture, srcRect, destRect);
    }

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

#endif //CAR_EXAMPLE_SCARS_H
