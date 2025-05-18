#include "Game.h"
#include "Snake.h"
#include "Food.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Menu.h"

Game::Game(SDL_Renderer* renderer)
    : snake(renderer),
      food(renderer),
      specialFood(renderer),
      specialFoodActive(false),
      score(0) {
    food.spawn();
    lastSpecialFoodTime = SDL_GetTicks();
}

Game::~Game() {
}

void Game::startNewGame(SDL_Renderer* renderer) {
    bool running = true;
    SDL_Event e;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            } else if (e.type == SDL_KEYDOWN) {
                snake.changeDirection(e.key.keysym.sym);
            }
        }

        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - lastSpecialFoodTime >= 15000 && !specialFoodActive) {
            specialFood.spawn();
            specialFoodActive = true;
            specialFoodSpawnTime = currentTime;
            lastSpecialFoodTime = currentTime;
        }
        if (specialFoodActive && currentTime - specialFoodSpawnTime >= 4000) {
            specialFoodActive = false;
        }

        SDL_Rect head = snake.getHead();
        SDL_Rect foodRect = food.getRect();
        SDL_Rect specialFoodRect = specialFood.getRect();
        bool ateFood = SDL_HasIntersection(&head, &foodRect);
        bool ateSpecialFood = specialFoodActive && SDL_HasIntersection(&head, &specialFoodRect);

        if (ateFood) {
            score += 1;
            food.spawn();
            snake.update(true);
        }
        if (ateSpecialFood) {
            score += 4;
            for (int i = 0; i < 4; ++i) {
                snake.update(true);
            }
            specialFoodActive = false;
        }
        if (!ateFood && !ateSpecialFood) {
            snake.update(false);
        }

        if (snake.isSelfCollision()) {
            std::cout << "Game Over. Score: " << score << std::endl;
            running = false;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        snake.render(renderer);
        food.render(renderer);
        if (specialFoodActive) {
            specialFood.render(renderer, true);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(125);
    }
}
