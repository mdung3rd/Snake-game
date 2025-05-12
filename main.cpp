#include <SDL2/SDL.h>
#include <iostream>
#include "Game.h"

int main(int argc, char* argv[]) {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "khong chay duoc game " << SDL_GetError() << std::endl;
        return 1;
    }

    Game game;
    game.run();


    SDL_Quit();
    return 0;
}
