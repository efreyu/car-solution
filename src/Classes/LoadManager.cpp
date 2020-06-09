#include "LoadManager.h"
#include "Game.h"

/**
 * Загрузка текстур из изображения.
 * @param fileName
 * @return
 */
SDL_Texture *LoadManager::LoadTexture(const char *fileName) {
    SDL_Surface* tempSurface = IMG_Load(fileName);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::mRenderer, tempSurface);

    SDL_FreeSurface(tempSurface);

    return texture;
}

/**
 * Рендер текстур
 * @param tex
 * @param src
 * @param dest
 */
void LoadManager::Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest) {
    SDL_RenderCopy(Game::mRenderer, tex, &src, &dest);
}

/**
 * Рендер текстуры с пддержкой поворота и флипа
 * @param tex
 * @param src
 * @param dest
 * @param angle
 * @param flip
 */
void LoadManager::DrawFlip(SDL_Texture * tex, SDL_Rect src, SDL_Rect dest, double angle, SDL_RendererFlip flip)
{
    SDL_RenderCopyEx(Game::mRenderer, tex, &src, &dest, angle, nullptr, flip);
}