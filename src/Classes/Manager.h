#ifndef CAR_EXAMPLE_MANAGER_H
#define CAR_EXAMPLE_MANAGER_H

#include <vector>
#include <string>
#include "sCars.h"
#include "GameObject.h"
#include "Creator.h"

class Manager {
protected:
    std::vector<Creator*> carTypes;
    std::vector<GameObject*> gameObjects;
    std::vector<bool> gameObjectsList;
    std::vector<sTransform> spawnPositions;
    int mCarWidth, mCarHeight, mCarPadding;
    float mCarScale;

public:
    Manager() {
        Init(70, 165, 20, 0.5f);
    }

    Manager(int carWidth, int carHeight, int carPadding, float carScale) {
        Init(carWidth, carHeight, carPadding, carScale);
    }

    void Init(int carWidth, int carHeight, int carPadding, float carScale) {
        auto [ width, height, scale ] = Game::GetWindowResolution();
        mCarWidth = carWidth;
        mCarHeight = carHeight;
        mCarPadding = carPadding;
        mCarScale = carScale * scale;
        /* top position */
        spawnPositions.emplace_back(sTransform(width / 2 + carPadding, 0, 0, 0, eDirection::DOWN));
        /* bottom position */
        spawnPositions.emplace_back(sTransform(width / 2 - carPadding, height, 0, 0, eDirection::UP));
        /* left position */
        spawnPositions.emplace_back(sTransform(0, height / 2 + carPadding, 0, 0, eDirection::RIGHT));
        /* right position */
        spawnPositions.emplace_back(sTransform(width, height / 2 - carPadding, 0, 0, eDirection::LEFT));
    }

    void Update() {
        for (auto& gameObject : gameObjects) {
            if (gameObject->isActive) gameObject->UpdateObject();
        }
    }

    void Draw() {
        for (auto& gameObject : gameObjects) {
            if (gameObject->isActive) gameObject->Draw();
        }
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
        auto n = std::rand() % carTypes.size();
        auto *car = carTypes[n]->GetObject();
        //Manipulation on car
        auto [ width, height, scale ] = Game::GetWindowResolution();
        //TODO It is only for testing =)
        car->transform.x = width / 2;
        car->transform.y = 0;
        car->transform.width = 70;
        car->transform.height = 165;
        car->transform.scale = 0.5f * scale;
        car->transform.direction = eDirection::DOWN;
        car->Refill(200);
        car->SetSpeed(3);
        //Store in manager array
        gameObjects.emplace_back(car);
    }

    void SpawnCar(int n) {
        for (int i = 0; i < n; i++) SpawnCar();
    }

    void GetRandomPosition() {
        std::srand(std::time(nullptr));
        auto n = std::rand() % 4;
        //
    }


};


#endif //CAR_EXAMPLE_MANAGER_H
