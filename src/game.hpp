/* Created by efreyu on 22.05.2020. */
#include <iostream>
#include <cstdlib>
#include <vector>

enum class eDirection {
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
public:
    sTransform transform;
    sCar() { speed = 0; };
    sCar(int speed, sTransform transform) : speed(speed), transform(transform) {};

    void move() {
        switch (transform.direction) {
            case eDirection::UP:
                transform.y += speed;
                break;
            case eDirection::RIGHT:
                transform.x += speed;
                break;
            case eDirection::DOWN:
                transform.y -= speed;
                break;
            case eDirection::LEFT:
                transform.x -= speed;
                break;
        }
        //TODO add fuel burn logic in move method
    }
    int getSpeed() { return speed; };
    int setSpeed(int i) { speed = i; };

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
    void move() { fuel--; sCar::move(); }
};

struct sElectroCar : virtual public sCar {
protected:
    int charge;
public:
    sElectroCar() : charge(0) {};
    int getFuel() { return charge; }
    void refill(int count) { charge += count; }
    void move() { charge--; sCar::move(); }
};

struct sHybridCar : virtual public sGasEngine, virtual public sElectroCar {
public:
    sHybridCar() {
        sGasEngine();
        sElectroCar();
    }
    void refill(int count) {
        /* используя тип int мы теряем 1 топливо каждый раз когда вызываем с нечетныйм параметром count */
        charge += count / 2; fuel += count / 2;
    }
    int getFuel() { return charge + fuel; }
    void move() {
        if (rand() % 2 == 0)
            sElectroCar::move();
        else
            sGasEngine::move();
    }
};