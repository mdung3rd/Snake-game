#include "Menu.h"
#include <iostream>

SDL_Texture* newGameTexture = nullptr;
SDL_Texture* settingsTexture = nullptr;
SDL_Texture* levelsTexture = nullptr;
SDL_Texture* quitTexture = nullptr;

SDL_Rect newGameButton = {200, 150, 300, 100};
SDL_Rect settingsButton = {200, 270, 300, 100};
SDL_Rect levelsButton = {200, 390, 300, 100};
SDL_Rect quitButton = {200, 510, 300, 100};

Menu::Menu() : selectedOption(0) {
    newGameButton = {200, 150, 300, 100};
    levelsButton = {200, 270, 300, 100};
    settingsButton = {200, 390, 300, 100};
    quitButton = {200, 510, 300, 100};
}

void Menu::render(SDL_Renderer* renderer) {
    // clear
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, newGameTexture, NULL, &newGameButton); // Nút "New Game"
    SDL_RenderCopy(renderer, settingsTexture, NULL, &settingsButton); // Nút "Settings"
    SDL_RenderCopy(renderer, levelsTexture, NULL, &levelsButton); // Nút "Levels"
    SDL_RenderCopy(renderer, quitTexture, NULL, &quitButton); // Nút "Quit"


    SDL_RenderPresent(renderer);
}

void Menu::handleEvent(SDL_Event& e) {

    handleMouseEvent(e);

    if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_DOWN) {
            selectedOption = (selectedOption + 1) % 4;
        } else if (e.key.keysym.sym == SDLK_UP) {
            selectedOption = (selectedOption - 1 + 4) % 4;
        } else if (e.key.keysym.sym == SDLK_RETURN) {

            std::cout << "Selected: " << menuOptions[selectedOption] << std::endl;
        }
    }
}

void Menu::handleMouseEvent(SDL_Event& e) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int x, y;
        SDL_GetMouseState(&x, &y);  //xac dinh vi tri chuot


        if (x >= newGameButton.x && x <= newGameButton.x + newGameButton.w &&
            y >= newGameButton.y && y <= newGameButton.y + newGameButton.h) {
            selectedOption = 0;  // new game
        }
        else if (x >= levelsButton.x && x <= levelsButton.x + levelsButton.w &&
                 y >= levelsButton.y && y <= levelsButton.y + levelsButton.h) {
            selectedOption = 1;  // level
        }
        else if (x >= settingsButton.x && x <= settingsButton.x + settingsButton.w &&
                 y >= settingsButton.y && y <= settingsButton.y + settingsButton.h) {
            selectedOption = 2;  // settings
        }
        else if (x >= quitButton.x && x <= quitButton.x + quitButton.w &&
                 y >= quitButton.y && y <= quitButton.y + quitButton.h) {
            selectedOption = 3;  // quit
        }
    }
}

int Menu::getSelectedOption() const {
    return selectedOption;
}
