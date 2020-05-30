#ifndef CAR_EXAMPLE_GAMEOBJECT_H
#define CAR_EXAMPLE_GAMEOBJECT_H

#include "sTransform.h"
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

    void LoadTexture(const std::string& path) {
        texture = LoadManager::LoadTexture((const char*)path.c_str());
    }

    void UpdateObject() {
        Update();
        UpdateTransform();
    }

    virtual void Update() {}

    void Draw() {
        LoadManager::Draw(texture, srcRect, destRect);
    }

private:
    void UpdateTransform() {
        srcRect.x = 0;
        srcRect.y = 0;
        srcRect.w = transform.width;
        srcRect.h = transform.height;
        destRect.w = transform.width * transform.scale;
        destRect.h = transform.height * transform.scale;
        destRect.x = transform.x;
        destRect.y = transform.y;
    }
};

#endif //CAR_EXAMPLE_GAMEOBJECT_H
