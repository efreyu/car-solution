/* Created by efreyu on 26.05.2020. */
#pragma once

#include <vector>
#include <string>
#include "sCars.h"
#include "Creator.h"

class Manager {
protected:
    std::vector<Creator*> carTypes;
    std::vector<sCar*> cars;
public:

    void move()
    {
        for (auto& car : cars) car->move();
    }

    template <typename T1, typename T2>
    void RegisterCarType(T2 arg) {
        T1 *car = new T1();
        //Manipulation on type
        car->SetTextures(arg);
        //Store in manager array
        carTypes.emplace_back(car);
    }

    void SpawnCar() {
        if (!carTypes.size()) return;

        std::srand(std::time(nullptr));
        auto n = std::rand()/((RAND_MAX + 1u)/(carTypes.size() - 1));
        auto *car = carTypes[n]->GetObject();
        //Manipulation on car
//        car->transform = transform;
        //Store in manager array
        cars.emplace_back(car);
    }

    void SpawnCar(int n) {
        for (int i = 0; i < n; i++) SpawnCar();
    }

};
