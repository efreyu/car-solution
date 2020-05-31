#ifndef CAR_EXAMPLE_MANAGER_H
#define CAR_EXAMPLE_MANAGER_H

#include <vector>
#include <string>
#include "sCars.h"
#include "GameObject.h"
#include "Creator.h"
#include "Collision.h"
#include "Random.h"

class Manager {
protected:
    std::vector<Creator*> carTypes;
    std::vector<GameObject*> gameObjects;
    std::vector<bool> gameObjectsList;
    std::vector<sTransform> spawnPositions;
    int mCarWidth, mCarHeight, mCarPadding, mCntSpawned;
    float mCarScale;

public:
    Manager() {
        Init(70, 165, 5, 0.5f);
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
        mCntSpawned = 0;
        /* top position */
        spawnPositions.emplace_back(sTransform(width / 2 - mCarPadding - mCarWidth, 0, mCarWidth, mCarHeight, eDirection::DOWN));
        /* bottom position */
        spawnPositions.emplace_back(sTransform(width / 2 + mCarPadding + mCarWidth, height, mCarWidth, mCarHeight, eDirection::UP));
        /* left position */
        spawnPositions.emplace_back(sTransform(0, height / 2 + mCarPadding + mCarWidth, mCarWidth, mCarHeight, eDirection::RIGHT));
        /* right position */
        spawnPositions.emplace_back(sTransform(width, height / 2 - mCarPadding - mCarWidth, mCarWidth, mCarHeight, eDirection::LEFT));
    }

    void Update() {
        QueueSpawnUpdate();
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

        auto n = Random::GenerateBetween(0, carTypes.size() - 1);
        auto *car = carTypes[n]->GetObject();
        //Manipulation on car
        car->transform.width = mCarWidth;
        car->transform.height = mCarHeight;
        car->transform.scale = mCarScale;
        car->Refill(200);
        car->SetSpeed(3);
        //Store in manager array
        gameObjects.emplace_back(car);
        gameObjectsList.emplace_back(false);
    }

    void SpawnCar(int n) {
        for (int i = 0; i < n; i++) SpawnCar();
    }

    /*
     * TODO
     *  1. метод для подсчета рандомной позиции для спавна
     *  2. метод проверки передвижения на карте
     */
private:
    void QueueSpawnUpdate() {
        for (int i = 0; i < gameObjectsList.size(); i++) {
            if(gameObjectsList[i]) continue;
            else if (mCntSpawned == 0) {
                //spawn first car
                auto s = spawnPositions.front();
                mCntSpawned++;
                gameObjectsList[i] = true;
                gameObjects[i]->transform.x = s.x;
                gameObjects[i]->transform.y = s.y;
                gameObjects[i]->transform.direction = s.direction;
                gameObjects[i]->isActive = true;
            } else {
                bool isSpawned = false;
                for (auto s : spawnPositions) {
                    bool isEmpty = true;
                    for (int l = 0; l < gameObjectsList.size(); l++) {
                        if(!gameObjectsList[i] && Collision::AABB(s, gameObjects[l]->transform, mCarPadding)) {
                            isEmpty = false;
                        }
                    }
                    if (isEmpty && !isSpawned) {
                        mCntSpawned++;
                        gameObjectsList[i] = true;
                        gameObjects[i]->transform.x = s.x;
                        gameObjects[i]->transform.y = s.y;
                        gameObjects[i]->transform.direction = s.direction;
                        gameObjects[i]->isActive = true;
                        isSpawned = true;
                    }
                }
            }
        }
    }

};


#endif //CAR_EXAMPLE_MANAGER_H
