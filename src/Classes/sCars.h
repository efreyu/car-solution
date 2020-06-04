#ifndef CAR_EXAMPLE_SCARS_H
#define CAR_EXAMPLE_SCARS_H

#include "GameObject.h"
#include "sTransform.h"

struct sCar : public GameObject {
private:
    int speed;
    int minSpeed = 1;

public:

    sCar() { speed = minSpeed; };
    sCar(int iSpeed, sTransform sTransform) {
        speed = iSpeed;
        transform = sTransform;
    };

    void Update() override {
        transform = GetNextPosition();
        FuelBurn();
    }

    sTransform GetNextPosition() override {
        sTransform nextTransform = transform;
        switch (nextTransform.direction) {
            case eDirection::UP:
                nextTransform.y -= GetSpeed();
                break;
            case eDirection::RIGHT:
                nextTransform.x += GetSpeed();
                break;
            case eDirection::DOWN:
                nextTransform.y += GetSpeed();
                break;
            case eDirection::LEFT:
                nextTransform.x -= GetSpeed();
                break;
        }
        return nextTransform;
    }

    sTransform GetRightPosition() override {
        sTransform tempTransform = transform;
        switch (tempTransform.direction) {
            case eDirection::DOWN:
                tempTransform.x -= tempTransform.width;
                tempTransform.y += tempTransform.height;
                break;
            case UP:
                tempTransform.x += tempTransform.width;
                tempTransform.y -= tempTransform.height;
                break;
            case RIGHT:
                tempTransform.y -= tempTransform.height;
                tempTransform.x += tempTransform.width;
                break;
            case LEFT:
                tempTransform.y += tempTransform.height;
                tempTransform.x -= tempTransform.width;
                break;
        }
        return tempTransform;
    }

    int GetSpeed() { return GetFuel() > 0 ? speed : minSpeed; };

    void SetSpeed(int i) { speed = i; };

    virtual void FuelBurn() = 0;

    virtual int GetFuel() = 0;

    virtual void Refill(int count) = 0;
};

struct sGasEngine : virtual public sCar {
protected:
    int fuel;

public:
    sGasEngine() : fuel(0) {}

    int GetFuel() override { return fuel; }

    void Refill(int count) override { fuel += count; }

    void FuelBurn() override {
        if (fuel > 0) fuel--;
    }
};

struct sElectroCar : virtual public sCar {
protected:
    int charge;

public:
    sElectroCar() : charge(0) {};

    int GetFuel() override { return charge; }

    void Refill(int count) override { charge += count; }

    void FuelBurn() override {
        if (charge > 0) charge--;
    }
};

struct sHybridCar : virtual public sGasEngine, virtual public sElectroCar {
public:
    sHybridCar() : sGasEngine(), sElectroCar() {};

    void Refill(int count) override {
        /* When we pass an odd number we always lose 1, due to int type casting.
         * The solution is to change the int to float for storing fuel, or use a temporary float variable.
         */
        charge += count / 2; fuel += count / 2;
    }

    int GetFuel() override { return charge + fuel; }

    void FuelBurn() override {
        if (rand() % 2 == 0)
            sElectroCar::FuelBurn();
        else
            sGasEngine::FuelBurn();
    }
};

#endif //CAR_EXAMPLE_SCARS_H
