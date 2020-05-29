#ifndef CAR_EXAMPLE_SCARS_H
#define CAR_EXAMPLE_SCARS_H

#include "GameObject.h"
#include "sTransform.h"

struct sCar : public GameObject {
private:
    int speed;
    int minSpeed = 1;

public:

    sCar() { speed = 0; };
    sCar(int speed, sTransform sTransform) {
        this->speed = speed;
        this->transform = sTransform;
    };

    void Update() {
        switch (transform.direction) {
            case eDirection::UP:
                transform.y += GetSpeed();
                break;
            case eDirection::RIGHT:
                transform.x += GetSpeed();
                break;
            case eDirection::DOWN:
                transform.y -= GetSpeed();
                break;
            case eDirection::LEFT:
                transform.x -= GetSpeed();
                break;
        }
        FuelBurn();
    }

    int GetSpeed() { return this->GetFuel() > 0 ? speed : minSpeed; };

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
    sHybridCar() {
        sGasEngine();
        sElectroCar();
    }

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
