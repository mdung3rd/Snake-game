#include "Menu.h"
#include <iostream>

Menu::Menu() : selectedOption(0) {}

void Menu::render(SDL_Renderer* renderer) {
    // clear
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);


    SDL_Color textColor = {255, 255, 255};

    // highlight
    for (int i = 0; i < 4; i++) {
        if (i == selectedOption) {
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        } else {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }


        std::cout << menuOptions[i] << std::endl;
    }

    SDL_RenderPresent(renderer);
}

void Menu::handleEvent(SDL_Event& e) {
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

int Menu::getSelectedOption() const {
    return selectedOption;
}
