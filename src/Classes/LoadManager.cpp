#include "LoadManager.h"
#include "Game.h"

SDL_Texture *LoadManager::LoadTexture(const char *fileName) {
    SDL_Surface* tempSurface = IMG_Load(fileName);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::mRenderer, tempSurface);

    SDL_FreeSurface(tempSurface);

    return texture;
}

void LoadManager::Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest) {
    SDL_RenderCopy(Game::mRenderer, tex, &src, &dest);
}