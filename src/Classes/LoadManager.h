#ifndef CAR_EXAMPLE_LOADMANAGER_H
#define CAR_EXAMPLE_LOADMANAGER_H

#include "Game.h"

class LoadManager {

public:
    static SDL_Texture* LoadTexture(const char *fileName);

    static void Draw(SDL_Texture * tex, SDL_Rect src, SDL_Rect dest);
};

#endif //CAR_EXAMPLE_LOADMANAGER_H
