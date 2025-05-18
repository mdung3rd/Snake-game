#pragma once
#include <SDL2/SDL.h>
#include "Snake.h"
#include "Food.h"

class Game {
public:
    Game();
    ~Game();
    void startNewGame(SDL_Renderer* renderer);
private:
    Snake snake;
    Food food;
    Food specialFood;
    bool specialFoodActive;
    Uint32 specialFoodSpawnTime;
    Uint32 lastSpecialFoodTime;
    int score;
};
