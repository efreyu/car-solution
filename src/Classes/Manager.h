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
    int mCarWidth, mCarHeight, mCarPadding, mCntSpawned;
    float mCarScale;

public:
    Manager() {
        Init(70, 165, 15, 0.5f);
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
        spawnPositions.emplace_back(sTransform(width / 2 + mCarPadding - mCarWidth, -mCarHeight, mCarWidth, mCarHeight, eDirection::DOWN, mCarScale));
        /* bottom position */
        spawnPositions.emplace_back(sTransform(width / 2 - mCarPadding + mCarWidth, height + carHeight, mCarWidth, mCarHeight, eDirection::UP, mCarScale));
        /* left position */
        spawnPositions.emplace_back(sTransform(-mCarWidth, height / 2 - mCarPadding + mCarWidth, mCarWidth, mCarHeight, eDirection::RIGHT, mCarScale, 90.0));
        /* right position */
        spawnPositions.emplace_back(sTransform(width+mCarWidth, height / 2 + mCarPadding - mCarWidth, mCarWidth, mCarHeight, eDirection::LEFT, mCarScale, 90.0));
    }

    void Update() {
        QueueSpawnUpdate();
        for (auto& gameObject : gameObjects) {
            if (gameObject->isActive && !HasCollision(*gameObject)) {
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
        car->SetSpeed(3);
        car->gameObjectId = gameObjects.size();
        //Store in manager array
        gameObjects.emplace_back(car);
    }

    void SpawnCar(int n) {
        for (int i = 0; i < n; i++) SpawnCar();
    }

private:
    void QueueSpawnUpdate() {
        // random spawn, only for fun =)
        if (Random::GenerateBetween(0,25) != 0) return;

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
                for (auto s : spawnPositions) {
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

    bool HasCollision(GameObject &gameObject) {
        for (auto const &a : gameObjects) {
            if (a->isActive && a->operator!=(gameObject) && (Collision::AABB(gameObject.GetNextPosition(), a->transform) ||
                Collision::AABB(gameObject.GetRightPosition(), a->transform))) {
                return true;
            }
        }
        return false;
    }

};


#endif //CAR_EXAMPLE_MANAGER_H
