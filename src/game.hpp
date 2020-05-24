/* Created by efreyu on 22.05.2020. */
#include <iostream>
#include <cstdlib>
#include <vector>

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
public:
    bool mIsRunning;
    Game() {
        init();
    }

    void init() {
        mIsRunning = true;
    }

    bool isRunning() const { return mIsRunning; }
};