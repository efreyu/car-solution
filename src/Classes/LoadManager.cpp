/* Created by efreyu on 24.05.2020. */

#include "LoadManager.h"

static SDL_Texture* LoadManager::LoadTexture(const char *fileName) {
    SDL_Surface* tempSurface = IMG_Load(fileName);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::mRenderer, tempSurface);

    SDL_FreeSurface(tempSurface);

    return texture;
}
static void LoadManager::Draw(SDL_Texture * tex, SDL_Rect src, SDL_Rect dest) {
    SDL_RenderCopy(Game::mRenderer, tex, &src, &dest);
}