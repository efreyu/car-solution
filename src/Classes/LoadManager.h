/* Created by efreyu on 24.05.2020. */
#pragma once

#include "Game.h"

class LoadManager {

public:
    static SDL_Texture* LoadTexture(const char *fileName) {
        SDL_Surface* tempSurface = IMG_Load(fileName);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::mRenderer, tempSurface);

        SDL_FreeSurface(tempSurface);

        return texture;
    }

    static void Draw(SDL_Texture * tex, SDL_Rect src, SDL_Rect dest) {
        SDL_RenderCopy(Game::mRenderer, tex, &src, &dest);
    }
};