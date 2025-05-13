#include "Game.h"
#include "Snake.h"
#include "Food.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "menu.h"

void Game::startNewGame(SDL_Renderer* renderer) {
    Snake snake;
    Food food;
    food.spawn();

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

        // Game logic: ăn mồi, va chạm...
        SDL_Rect head = snake.getHead();
        SDL_Rect foodRect = food.getRect();
        bool ateFood = SDL_HasIntersection(&head, &foodRect);

        if (ateFood) {
            food.spawn();
        }
        snake.update(ateFood);

        // Kiểm tra va chạm
        if (snake.isSelfCollision()) {
            std::cout << "Game Over" << std::endl;
            running = false;
        }

        // Vẽ game
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        snake.render(renderer);
        food.render(renderer);

        SDL_RenderPresent(renderer);
        SDL_Delay(125);
    }
}
