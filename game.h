#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

class Game {
public:
    void run();
    void startNewGame(SDL_Renderer* renderer);
};

#endif
