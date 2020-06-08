#ifndef CAR_EXAMPLE_MANAGER_H
#define CAR_EXAMPLE_MANAGER_H

#include <vector>
#include <string>
#include <map>
#include "sCars.h"
#include "GameObject.h"
#include "Creator.h"
#include "Collision.h"
#include "Random.h"



class Manager {
protected:
    std::vector<Creator*> carTypes;
    std::vector<GameObject*> gameObjects;
    std::vector<sTransform> spawnPositions;
    sTransform *crossroads;
    int mCarWidth, mCarHeight, mCarPadding;
    float mCarScale;
    int mCntSpawned, mCntRegistered;

public:
    Manager() {
        Init(70, 165, 0.5f);
    }

    Manager(int carWidth, int carHeight, float carScale) {
        Init(carWidth, carHeight, carScale);
    }

    void Init(int carWidth, int carHeight, float carScale) {
        auto [ width, height, scale ] = Game::GetWindowResolution();
        mCarWidth = carWidth;
        mCarHeight = carHeight;
        mCarScale = carScale * scale;
        mCntSpawned = mCntRegistered = 0;

        /* top position */
        spawnPositions.emplace_back(sTransform(width / 2 - mCarWidth * mCarScale, -mCarHeight, mCarWidth, mCarHeight, eDirection::DOWN, mCarScale));
        /* bottom position */
        spawnPositions.emplace_back(sTransform(width / 2  + mCarWidth * mCarScale, height + mCarHeight, mCarWidth, mCarHeight, eDirection::UP, mCarScale));
        /* left position */
        spawnPositions.emplace_back(sTransform(0 - mCarWidth, height / 2  + mCarWidth * mCarScale, mCarWidth, mCarHeight, eDirection::RIGHT, mCarScale, 90.0));
        /* right position */
        spawnPositions.emplace_back(sTransform(width+mCarWidth, height / 2 - mCarWidth * mCarScale, mCarWidth, mCarHeight, eDirection::LEFT, mCarScale, 90.0));

        crossroads = new sTransform(width / 2 - mCarWidth * mCarScale / 2 * 3, height / 2  - mCarWidth * mCarScale / 2 * 3, mCarHeight * mCarScale * 2, mCarHeight * mCarScale * 2);
    }

    void Update() {
        ReinitObjects();
        QueueSpawnUpdate();
        for (auto& gameObject : gameObjects) {
            if (gameObject->isActive && !HasCollision(*gameObject) && CanPassCrossroads(*gameObject)) {
                gameObject->UpdateObject();
            }
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
        car->SetSpeed(3 * std::get<2>(Game::GetWindowResolution()));
        car->SetMinSpeed(1 * std::get<2>(Game::GetWindowResolution()));
        car->gameObjectId = mCntRegistered++;
        //Store in manager array
        gameObjects.emplace_back(car);
    }

    void SpawnCar(int n) {
        for (int i = 0; i < n; i++) SpawnCar();
    }

private:
    void QueueSpawnUpdate() {
        // random spawn, only for fun =)
        if (Random::GenerateBetween(0,15) != 0) return;

        bool isSpawned = false;
        for (auto item : gameObjects) {
            if (item->isActive || isSpawned) continue;
            else if (mCntSpawned == 0) {
                //spawn first car
                auto s = spawnPositions.front();
                mCntSpawned++;
                item->transform.x = s.x;
                item->transform.y = s.y;
                item->transform.direction = s.direction;
                item->isActive = true;
            } else {
//                bool isSpawned = false;
                for (int i = 0; i < 4; i++) {
                    auto s = Random::GetRandomVector<sTransform>(spawnPositions);
                    bool isEmpty = true;
                    for (auto const &l : gameObjects) {
                        if(l->isActive && Collision::AABB(s, l->transform)) {
                            isEmpty = false;
                        }
                    }
                    if (isEmpty && !isSpawned) {
                        mCntSpawned++;
                        item->transform.x = s.x;
                        item->transform.y = s.y;
                        item->transform.direction = s.direction;
                        item->isActive = true;
                        isSpawned = true;
                    }
                }
            }
        }
    }

    void ReinitObjects() {
        if (gameObjects.size() < 20) {
            SpawnCar(5);
        }
        for (int i = 0; i < gameObjects.size(); i++) {
            if (gameObjects[i]->isDestroyed) {
                gameObjects.erase(gameObjects.begin() + i, gameObjects.begin() + i + 1);
            }
        }
    }

    bool HasCollision(GameObject &gameObject) {
        for (auto const &a : gameObjects) {
            if (a->isActive && a->operator!=(gameObject) && Collision::AABB(gameObject.GetNextPosition(), a->transform)) {
                return true;
            }
        }
        return false;
    }

    bool CanPassCrossroads(GameObject &gameObject) {
        if (!Collision::AABB(gameObject.GetNextPosition(), *crossroads))
            return true;

        //3. Пропускаем того кто справа
        //4. Пропусаем того кто имееет x < 0
        std::vector<GameObject> objects = {};
        for(auto &a : gameObjects) {
            if (a->isActive && Collision::AABB(a->GetNextPosition(), *crossroads)) {
                auto obj = new GameObject();
                obj->gameObjectId = a->gameObjectId;
                obj->transform = sTransform(
                        a->transform.x, a->transform.y,
                        a->transform.width * a->transform.scale,
                        a->transform.height * a->transform.scale);

                objects.emplace_back(*obj);
            }
        }
        //1. Пропускаем если машина одна
        if (objects.size() == 1 && gameObject.operator==(objects[0])) return true;
        //2. Пропускаем того кто ближе к центру (машина проезжает)
//        if (objects.size() == 4) {
//
//        }
        std::cout << objects.size() << std::endl;
        return false;
    }


};


#endif //CAR_EXAMPLE_MANAGER_H
