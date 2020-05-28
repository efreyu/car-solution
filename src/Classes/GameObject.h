#ifndef CAR_EXAMPLE_GAMEOBJECT_H
#define CAR_EXAMPLE_GAMEOBJECT_H

#include "Transform.h"
#include "LoadManager.h"

class GameObject {
public:
    sTransform transform;
    SDL_Texture *texture{};
    SDL_Rect srcRect{}, destRect{};
    bool isActive;
    bool isDestroyed;

    GameObject() : isActive(false), isDestroyed(false) {};

    ~GameObject() {
        SDL_DestroyTexture(texture);
    }

    void LoadTexture(std::string path) {
        texture = LoadManager::LoadTexture((const char*)path.c_str());
    }

    void Init() {
        //TODO call this when GO was spawned
    }

    void Update();

    void Draw() {
        LoadManager::Draw(texture, srcRect, destRect);
    }
};

#endif //CAR_EXAMPLE_GAMEOBJECT_H
