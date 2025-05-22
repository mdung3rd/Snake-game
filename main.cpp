#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Game.h"
#include "Menu.h"

void showMenu(SDL_Renderer* renderer) {
    SDL_Texture* backgroundTexture = IMG_LoadTexture(renderer, "assets/images/menu.png");
    if (!backgroundTexture) {
        std::cerr << "tai anh nen bi loi " << SDL_GetError() << std::endl;
        return;
    }

    SDL_Texture* newGameTexture = IMG_LoadTexture(renderer, "assets/images/new_game.png");
    SDL_Texture* settingsTexture = IMG_LoadTexture(renderer, "assets/images/settings.png");
    SDL_Texture* levelsTexture = IMG_LoadTexture(renderer, "assets/images/levels.png");
    SDL_Texture* quitTexture = IMG_LoadTexture(renderer, "assets/images/quit.png");
    SDL_Texture* easyTexture = IMG_LoadTexture(renderer, "assets/images/easy.png");
    SDL_Texture* hardTexture = IMG_LoadTexture(renderer, "assets/images/hard.png");
    SDL_Texture* specialTexture = IMG_LoadTexture(renderer, "assets/images/special.png");
    SDL_Texture* backTexture = IMG_LoadTexture(renderer, "assets/images/back.png");
    SDL_Texture* notificationTexture = IMG_LoadTexture(renderer, "assets/images/notification.png");

    SDL_Texture* reverseSnakeTexture = IMG_LoadTexture(renderer, "assets/images/reverse_snake.png");
    SDL_Texture* tickTexture = IMG_LoadTexture(renderer, "assets/images/tick.png");

    if (!newGameTexture || !settingsTexture || !levelsTexture || !quitTexture || !easyTexture || !hardTexture || !specialTexture || !backTexture || !notificationTexture || !reverseSnakeTexture || !tickTexture) { std::cerr << "tai menu bi loi " << SDL_GetError() << std::endl;SDL_DestroyTexture(backgroundTexture);
        return;
    }

    SDL_Rect newGameButton = {200, 150, 300, 100};
    SDL_Rect settingsButton = {200, 270, 300, 100};
    SDL_Rect levelsButton = {200, 390, 300, 100};
    SDL_Rect quitButton = {200, 510, 300, 100};
    SDL_Rect easyButton = {200, 150, 300, 100};
    SDL_Rect hardButton = {200, 270, 300, 100};
    SDL_Rect specialButton = {200, 390, 300, 100};
    SDL_Rect backButton = {1100, 600, 150, 100};
    SDL_Rect notificationRect = {640 - 150, 50, 300, 80};
    SDL_Rect reverseSnakeRect = {1280 / 2 - 150, 720 / 2 - 50, 300, 100};

    bool isMenuActive = true;
    bool reverseMode = false;

    while (isMenuActive) {
        Menu menu;
        bool isLevelsMenuActive = false;
        bool isSettingsMenuActive = false;
        int selectedLevel = -1;
        bool showNotification = false;
        bool hasNotified = false;

        while (isMenuActive) {
            SDL_Event e;
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    isMenuActive = false;
                }
                if (!isLevelsMenuActive && !isSettingsMenuActive) {
                    menu.handleEvent(e, newGameButton, settingsButton, levelsButton, quitButton, easyButton, hardButton, specialButton, backButton, isLevelsMenuActive, isSettingsMenuActive);
                } else if (isLevelsMenuActive) {
                    menu.handleEvent(e, easyButton, hardButton, specialButton, quitButton, easyButton, hardButton, specialButton, backButton, isLevelsMenuActive, isSettingsMenuActive);
                } else if (isSettingsMenuActive) {
                    if (e.type == SDL_MOUSEBUTTONDOWN) {
                        int mouseX = e.button.x;
                        int mouseY = e.button.y;
                        if (mouseX >= reverseSnakeRect.x && mouseX <= reverseSnakeRect.x + reverseSnakeRect.w && mouseY >= reverseSnakeRect.y && mouseY <= reverseSnakeRect.y + reverseSnakeRect.h) {
                            reverseMode = !reverseMode;
                        }
                    }
                    menu.handleEvent(e, easyButton, hardButton, specialButton, backButton, easyButton, hardButton, specialButton, backButton, isLevelsMenuActive, isSettingsMenuActive);
                }
            }

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            if (isLevelsMenuActive) {
                easyButton.w = 300; easyButton.h = 100;
                hardButton.w = 300; hardButton.h = 100;
                specialButton.w = 300; specialButton.h = 100;
                if (selectedLevel == 10) {
                    easyButton.w = 330; easyButton.h = 110;
                    easyButton.x = 200 - (330 - 300) / 2;
                    easyButton.y = 150 - (110 - 100) / 2;
                } else if (selectedLevel == 11) {
                    hardButton.w = 330; hardButton.h = 110;
                    hardButton.x = 200 - (330 - 300) / 2;
                    hardButton.y = 270 - (110 - 100) / 2;
                } else if (selectedLevel == 12) {
                    specialButton.w = 330; specialButton.h = 110;
                    specialButton.x = 200 - (330 - 300) / 2;
                    specialButton.y = 390 - (110 - 100) / 2;
                }
            }

            if (!isLevelsMenuActive && !isSettingsMenuActive) {
                SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
                SDL_RenderCopy(renderer, newGameTexture, NULL, &newGameButton);
                SDL_RenderCopy(renderer, settingsTexture, NULL, &settingsButton);
                SDL_RenderCopy(renderer, levelsTexture, NULL, &levelsButton);
                SDL_RenderCopy(renderer, quitTexture, NULL, &quitButton);
            } else if (isLevelsMenuActive) {
                SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
                SDL_RenderCopy(renderer, easyTexture, NULL, &easyButton);
                SDL_RenderCopy(renderer, hardTexture, NULL, &hardButton);
                SDL_RenderCopy(renderer, specialTexture, NULL, &specialButton);
                SDL_RenderCopy(renderer, backTexture, NULL, &backButton);
            } else if (isSettingsMenuActive) {
                SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
                SDL_RenderCopy(renderer, reverseSnakeTexture, NULL, &reverseSnakeRect);
                if (reverseMode) {
                    SDL_Rect tickRect = {reverseSnakeRect.x + (reverseSnakeRect.w - 50) / 2 + 103, reverseSnakeRect.y + (reverseSnakeRect.h - 50) / 2, 50, 50};
                    SDL_RenderCopy(renderer, tickTexture, NULL, &tickRect);
                }
                SDL_RenderCopy(renderer, backTexture, NULL, &backButton);
            }

            if (showNotification && selectedLevel == -1) {
                if (notificationTexture) SDL_RenderCopy(renderer, notificationTexture, NULL, &notificationRect);
            } else {
                showNotification = false;
                hasNotified = false;
            }

            int selectedOption = menu.getSelectedOption();
            if (selectedOption != -1) {
                if (selectedOption == 0) { // new game
                    if (selectedLevel == -1) {
                        if (!hasNotified) {
                            std::cout << "choose level!" << std::endl;
                            hasNotified = true;
                        }
                        showNotification = true;
                    } else if (selectedLevel == 10) { // Easy
                        std::cout << "game started(easy mode)" << std::endl;
                        isMenuActive = false;
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                        SDL_RenderClear(renderer);
                        SDL_RenderPresent(renderer);
                        Game game(renderer, 0, reverseMode);
                        game.startNewGame(renderer, 150);
                        if (game.isExitToMenu()) {
                            isMenuActive = true;
                            break;
                        }
                    } else if (selectedLevel == 11) { // Hard
                        std::cout << "game started(hard mode)" << std::endl;
                        isMenuActive = false;
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                        SDL_RenderClear(renderer);
                        SDL_RenderPresent(renderer);
                        Game game(renderer, 1, reverseMode);
                        game.startNewGame(renderer, 50);
                        if (game.isExitToMenu()) {
                            isMenuActive = true;
                            break;
                        }
                    } else if (selectedLevel == 12) { // Special
                        std::cout << "special mode started" << std::endl;
                        isMenuActive = false;
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                        SDL_RenderClear(renderer);
                        SDL_RenderPresent(renderer);
                        Game game(renderer, 2, reverseMode);
                        game.startNewGame(renderer, 100);
                        if (game.isExitToMenu()) {
                            isMenuActive = true;
                            break;
                        }
                    }
                } else if (selectedOption == 1) { // Levels
                    std::cout << "Opening Levels menu" << std::endl;
                    isLevelsMenuActive = true;
                    menu = Menu();
                } else if (selectedOption == 2) { // Settings
                    std::cout << "Opening Settings menu" << std::endl;
                    isSettingsMenuActive = true;
                    menu = Menu();
                } else if (selectedOption == 3) { // Quit
                    std::cout << "Quit selected" << std::endl;
                    isMenuActive = false;
                } else if (selectedOption == 4) { // Back
                    std::cout << "Returning to main menu" << std::endl;
                    isLevelsMenuActive = false;
                    isSettingsMenuActive = false;
                    menu = Menu();
                } else if (isLevelsMenuActive) {
                    if (selectedOption == 10) { // Easy
                        std::cout << "Selected Easy mode" << std::endl;
                        selectedLevel = 10;
                        menu = Menu();
                    } else if (selectedOption == 11) { // Hard
                        std::cout << "Selected Hard mode" << std::endl;
                        selectedLevel = 11;
                        menu = Menu();
                    } else if (selectedOption == 12) { // Special
                        std::cout << "Selected Special mode" << std::endl;
                        selectedLevel = 12;
                        menu = Menu();
                    }
                }
            }

            SDL_RenderPresent(renderer);
            if (SDL_GetError()[0] != '\0') {
                std::cerr << "error in menu " << SDL_GetError() << std::endl;
                SDL_ClearError();
            }
            SDL_Delay(10);
        }
    }

    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(newGameTexture);
    SDL_DestroyTexture(settingsTexture);
    SDL_DestroyTexture(levelsTexture);
    SDL_DestroyTexture(quitTexture);
    SDL_DestroyTexture(easyTexture);
    SDL_DestroyTexture(hardTexture);
    SDL_DestroyTexture(specialTexture);
    SDL_DestroyTexture(backTexture);
    SDL_DestroyTexture(notificationTexture);
    SDL_DestroyTexture(reverseSnakeTexture);
    SDL_DestroyTexture(tickTexture);
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "khong tao duoc SDL " << SDL_GetError() << std::endl;
        return 1;
    }
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        std::cerr << "Khong tao duoc SDL image: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    SDL_Window* window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
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
