#pragma once
#include <SDL2/SDL.h>
#include "Snake.h"
#include "Food.h"

class Game {
public:
    Game(SDL_Renderer* renderer);
    ~Game();
    void startNewGame(SDL_Renderer* renderer, int delayMs);
    bool isPaused() const;
    bool isExitToMenu() const;

private:
    Snake snake;
    Food food;
    Food specialFood;
    bool specialFoodActive;
    Uint32 specialFoodSpawnTime;
    Uint32 lastSpecialFoodTime;
    int score;
    bool paused;
    bool exitToMenu;
    SDL_Renderer* renderer;
    SDL_Texture* notificationTexture;
    SDL_Rect notificationRect;
};
