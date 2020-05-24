#include "game.hpp"

Game *game = nullptr;

void game_loop()
{
    while (game->isRunning()) {
        game->GameLoop();
    }

    game->Quit();
}

void wasm_game_loop()
{
    if (game->isRunning()) {
        game->GameLoop();
    } else {
        game->Quit();
#ifdef __EMSCRIPTEN__
        emscripten_cancel_main_loop();
#endif
    }
}

extern "C" {
void window_resize(int width, int height) {
    game->WindowResize(width, height);
}
}

int main()
{
    game = new Game();
    game->Init("Car example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, false);

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(wasm_game_loop, 0, 1);
#else
    game_loop();
#endif //EMSCRIPTEN_IS_USED

    return 0;
}