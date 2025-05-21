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
      score(0),
      paused(false),
      exitToMenu(false),
      renderer(renderer) {
    food.spawn();
    lastSpecialFoodTime = SDL_GetTicks();
    // thong bao2
    notificationTexture = IMG_LoadTexture(renderer, "assets/images/notification2.png");
    if (!notificationTexture) {
        std::cerr << "khong tai duoc thong bao 2 " << SDL_GetError() << std::endl;
    }
    notificationRect = {640 - 150, 50, 300, 80};
}

Game::~Game() {
    if (notificationTexture) {
        SDL_DestroyTexture(notificationTexture);
    }
}

void Game::startNewGame(SDL_Renderer* renderer, int delayMs) {
    bool running = true;
    SDL_Event e;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            } else if (e.type == SDL_KEYDOWN) {
                if (!paused) {
                    snake.changeDirection(e.key.keysym.sym);
                }
                //xu li phim
                switch (e.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        paused = true; // esc = pause game
                        break;
                    case SDLK_y:
                        if (paused) {
                            exitToMenu = true;
                            running = false;
                        }
                        break;
                    case SDLK_n:
                        if (paused) {
                            paused = false;
                        }
                        break;
                }
            }
        }

            if (!paused) {
            Uint32 currentTime = SDL_GetTicks();
            // moi dac biet
            if (currentTime - lastSpecialFoodTime >= 15000 && !specialFoodActive) {
                specialFood.spawn();
                specialFoodActive = true;
                specialFoodSpawnTime = currentTime;
                lastSpecialFoodTime = currentTime;
            }

            if (specialFoodActive && currentTime - specialFoodSpawnTime >= 7000) {
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
        }

        // Render
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        snake.render(renderer);
        food.render(renderer);
        if (specialFoodActive) {
            specialFood.render(renderer, true);
        }

        // tao thong bao khi dang tam dung
        if (paused && notificationTexture) {
            SDL_RenderCopy(renderer, notificationTexture, NULL, &notificationRect);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(delayMs);
    }
}

bool Game::isPaused() const {
    return paused;
}

bool Game::isExitToMenu() const {
    return exitToMenu;
}
