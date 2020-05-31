#ifndef CAR_EXAMPLE_GAMEOBJECT_H
#define CAR_EXAMPLE_GAMEOBJECT_H

#include "sTransform.h"
#include "LoadManager.h"

class GameObject {
public:
    sTransform transform;
    SDL_Texture *texture{};
    SDL_Rect srcRect{}, destRect{};
    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
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

    void Draw() const {
        LoadManager::DrawFlip(texture, srcRect, destRect, transform.angle, spriteFlip);
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
        //flip sprite
        switch (transform.direction) {
            case eDirection::UP:
                spriteFlip = SDL_FLIP_VERTICAL;
                break;
            case eDirection::RIGHT:
                transform.angle = -90.0;
                break;
            case eDirection::LEFT:
                transform.angle = 90.0;
                break;
            default:
                spriteFlip = SDL_FLIP_NONE;
                transform.angle = 0.0;
        }
    }
};

#endif //CAR_EXAMPLE_GAMEOBJECT_H
