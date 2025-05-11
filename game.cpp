#include "Game.h"
#include "Snake.h"
#include <SDL2/SDL.h>
#include <iostream>
#include "Food.h"
#include "Menu.h"
#include <SDL2/SDL_image.h>

void Game::run() {

    SDL_Window* window = SDL_CreateWindow(
        "Snake Game",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1280, 720,
        SDL_WINDOW_SHOWN
    );

    if (window == nullptr) {
        std::cerr << " khong the tao cua so " << SDL_GetError() << std::endl;
        return;
    }


    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "khong the tao cua so"  << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        return;
    }

    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        std::cerr << "error " << SDL_GetError() << std::endl;
        return;
    }


    SDL_Texture* backgroundTexture = IMG_LoadTexture(renderer, "assets/images/menu.png");
    if (!backgroundTexture) {
        std::cerr << "Lỗi khi tải ảnh nền: " << SDL_GetError() << std::endl;
        return;
    }

    Menu menu;
    bool isMenuActive = true;

    while (isMenuActive) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                isMenuActive = false;
            }
            menu.handleEvent(e);
        }
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

    menu.render(renderer);

    if (menu.getSelectedOption() == 0) {

        //khoi tao game o day

        isMenuActive = false;

    }

        SDL_Delay(100);
    }

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

    SDL_Rect head = snake.getHead();
    SDL_Rect foodRect = food.getRect();
    bool ateFood = SDL_HasIntersection(&head, &foodRect);

    if (ateFood) {
        food.spawn();
    }
    snake.update(ateFood);

    // va cham voi duoi -> game over
    if (snake.isSelfCollision()) {
        std::cout << "Game over" << std::endl;
        running = false;
    }

    //don man hinh va ve lai
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    snake.render(renderer);
    food.render(renderer);

    SDL_RenderPresent(renderer);

    SDL_Delay(125);
    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
