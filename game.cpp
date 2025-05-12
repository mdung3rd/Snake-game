#include "Game.h"
#include "Snake.h"
#include <SDL2/SDL.h>
#include <iostream>
#include "Food.h"
#include "Menu.h"
#include <SDL2/SDL_image.h>



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

        // an moi
        SDL_Rect head = snake.getHead();
        SDL_Rect foodRect = food.getRect();
        bool ateFood = SDL_HasIntersection(&head, &foodRect);

        if (ateFood) {
            food.spawn();
        }
        snake.update(ateFood);

        // kiem tra va cham
        if (snake.isSelfCollision()) {
            std::cout << "Game Over" << std::endl;
            running = false;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //ve lai ran va moi
        snake.render(renderer);
        food.render(renderer);

        SDL_RenderPresent(renderer);
        SDL_Delay(125);
    }

    SDL_DestroyTexture(newGameTexture);
    SDL_DestroyTexture(settingsTexture);
    SDL_DestroyTexture(levelsTexture);
    SDL_DestroyTexture(quitTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
}

