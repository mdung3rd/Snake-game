#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Game.h"
#include "Menu.h"

void showMenu(SDL_Renderer* renderer) {

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
        SDL_DestroyTexture(backgroundTexture);
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
                isMenuActive = false;
            }

            menu.handleEvent(e, newGameButton, settingsButton, levelsButton, quitButton);
        }

        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
        SDL_RenderCopy(renderer, newGameTexture, NULL, &newGameButton);
        SDL_RenderCopy(renderer, settingsTexture, NULL, &settingsButton);
        SDL_RenderCopy(renderer, levelsTexture, NULL, &levelsButton);
        SDL_RenderCopy(renderer, quitTexture, NULL, &quitButton);

        int selectedOption = menu.getSelectedOption();
        if (selectedOption == 0) {
            isMenuActive = false;
            Game game;
            game.startNewGame(renderer);
        } else if (selectedOption == 1) {
            std::cout << "Levels selected" << std::endl;
        } else if (selectedOption == 2) {
            std::cout << "Settings selected" << std::endl;
        } else if (selectedOption == 3) {
            // quit
            isMenuActive = false;
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }

    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(newGameTexture);
    SDL_DestroyTexture(settingsTexture);
    SDL_DestroyTexture(levelsTexture);
    SDL_DestroyTexture(quitTexture);
}

int main(int argc, char* argv[]) {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "khong khoi tao duoc sdl " << SDL_GetError() << std::endl;
        return 1;
    }

    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        std::cerr << "khong tao sdl image " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }


    SDL_Window* window = SDL_CreateWindow(
        "Snake Game",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1280, 720,
        SDL_WINDOW_SHOWN
    );
    if (!window) {
        std::cerr << "khong tao duoc cua so " << SDL_GetError() << std::endl;
        IMG_Quit();
        SDL_Quit();
        return 1;
    }


    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "render bi loi " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    showMenu(renderer);


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
