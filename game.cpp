#include "Game.h"
#include "Snake.h"
#include "Food.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Menu.h"

Game::Game() {
    food.spawn();
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

        SDL_Rect head = snake.getHead();
        SDL_Rect foodRect = food.getRect();
        bool ateFood = SDL_HasIntersection(&head, &foodRect);

        if (ateFood) {
            food.spawn();
        }
        snake.update(ateFood);

        if (head.x < 0 || head.x >= 1280 || head.y < 0 || head.y >= 720) {
            std::cout << "Game Over: Hit the wall!" << std::endl;
            running = false;
        }

        if (snake.isSelfCollision()) {
            std::cout << "Game Over: Self-collision!" << std::endl;
            running = false;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        snake.render(renderer);
        food.render(renderer);

        SDL_RenderPresent(renderer);
        SDL_Delay(125);
    }
}



