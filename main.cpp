#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Game.h"
#include "Menu.h"


void showMenu() {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "khong khoi tao duoc sdl " << SDL_GetError() << std::endl;
        return;
    }


    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        std::cerr << "khong tao sdl image " << SDL_GetError() << std::endl;
        return;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Snake Game",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1280, 720,
        SDL_WINDOW_SHOWN
    );

    if (window == nullptr) {
        std::cerr << "khong tao duoc cua so " << SDL_GetError() << std::endl;
        return;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "render bi loi " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        return;
    }

    //tai anh nen
    SDL_Texture* backgroundTexture = IMG_LoadTexture(renderer, "assets/images/menu.png");
    if (!backgroundTexture) {
        std::cerr << "khong tai duoc anh nen " << SDL_GetError() << std::endl;
        return;
    }

    SDL_Texture* newGameTexture = IMG_LoadTexture(renderer, "assets/images/new_game.png");
    SDL_Texture* settingsTexture = IMG_LoadTexture(renderer, "assets/images/settings.png");
    SDL_Texture* levelsTexture = IMG_LoadTexture(renderer, "assets/images/levels.png");
    SDL_Texture* quitTexture = IMG_LoadTexture(renderer, "assets/images/quit.png");

    if (!newGameTexture || !settingsTexture || !levelsTexture || !quitTexture) {
        std::cerr << "khong tai duoc cac nut menu " << SDL_GetError() << std::endl;
        return;
    }

    SDL_Rect newGameButton = {200, 150, 300, 100};
    SDL_Rect settingsButton = {200, 270, 300, 100};
    SDL_Rect levelsButton = {200, 390, 300, 100};
    SDL_Rect quitButton = {200, 510, 300, 100};

    Menu menu;

    bool isMenuActive = true;
    while (isMenuActive) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                isMenuActive = false;  // neu dong cua so thi thoat game
            }
            menu.handleEvent(e);
        }


        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);


        SDL_RenderCopy(renderer, newGameTexture, NULL, &newGameButton);
        SDL_RenderCopy(renderer, settingsTexture, NULL, &settingsButton);
        SDL_RenderCopy(renderer, levelsTexture, NULL, &levelsButton);
        SDL_RenderCopy(renderer, quitTexture, NULL, &quitButton);

        if (menu.getSelectedOption() == 0) {
            isMenuActive = false;
            startNewGame(renderer);
        } else if (menu.getSelectedOption() == 1) {
            // level
        } else if (menu.getSelectedOption() == 2) {
            // setting
        } else if (menu.getSelectedOption() == 3) {
            isMenuActive = false;  // exit game
            break;
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
        }


    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(newGameTexture);
    SDL_DestroyTexture(settingsTexture);
    SDL_DestroyTexture(levelsTexture);
    SDL_DestroyTexture(quitTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    showMenu();
    return 0;
}

