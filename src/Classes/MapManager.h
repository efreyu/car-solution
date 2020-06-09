#ifndef CAR_EXAMPLE_MAPMANAGER_H
#define CAR_EXAMPLE_MAPMANAGER_H

#include <vector>
#include "GameObject.h"

class MapManager {
protected:
    std::vector<GameObject*> groundObjects;
    int windowWidth, windowHeight;
    float windowScale;


public:
    MapManager() {
        auto [ width, height, scale ] = Game::GetWindowResolution();
        windowWidth = width;
        windowHeight = height;
        windowScale = scale;
    }

    void Update() {
        for (auto& groundObject : groundObjects) {
            groundObject->UpdateObject();
        }
    }

    void Draw() {
        for (auto& groundObject : groundObjects) {
            groundObject->Draw();
        }
    }

    void InitGroundTexture(char const* path, int imgWidth, int imgHeight) {
        for (int i = 0; i < windowWidth / imgWidth + 1; ++i) {
            for (int j = 0; j < windowHeight / imgHeight + 1; ++j) {
                auto *ground = new GameObject();
                ground->transform.width = imgWidth * windowScale;
                ground->transform.height = imgHeight * windowScale;
                ground->transform.x = imgWidth * i * windowScale;
                ground->transform.y = imgHeight * j * windowScale;
                ground->LoadTexture(path);

                groundObjects.emplace_back(ground);
            }
        }
    }

    void InitRoadTexture(char const* path, int imgWidth, int imgHeight) {
        for (int i = 0; i < windowWidth / imgWidth + 1; ++i) {
            auto *ground = new GameObject();
            ground->transform.width = imgWidth * windowScale;
            ground->transform.height = imgHeight * windowScale;
            ground->transform.x = imgWidth * i * windowScale;
            ground->transform.y = windowHeight / 2 - ground->transform.height / 2;
            ground->LoadTexture(path);

            groundObjects.emplace_back(ground);
        }
        for (int i = 0; i < windowHeight / imgHeight + 1; ++i) {
            auto *ground = new GameObject();
            ground->transform.width = imgWidth * windowScale;
            ground->transform.height = imgHeight * windowScale;
            ground->transform.x = windowWidth / 2 - ground->transform.width / 2;
            ground->transform.y = imgHeight * i * windowScale;
            ground->transform.direction = eDirection::RIGHT;
            ground->LoadTexture(path);

            groundObjects.emplace_back(ground);
        }
    }

    void InitCrossroadTexture(char const* path, int imgWidth, int imgHeight) {
        auto *ground = new GameObject();
        ground->transform.width = imgWidth * windowScale;
        ground->transform.height = imgHeight * windowScale;
        ground->transform.x = windowWidth / 2 - ground->transform.width / 2;
        ground->transform.y = windowHeight / 2 - ground->transform.height / 2;
        ground->LoadTexture(path);

        groundObjects.emplace_back(ground);
    }
};
#endif //CAR_EXAMPLE_MAPMANAGER_H
