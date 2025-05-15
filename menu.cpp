#include "Menu.h"

Menu::Menu() : selectedOption(-1) {}

void Menu::handleEvent(const SDL_Event& e, const SDL_Rect& newGameButton, const SDL_Rect& settingsButton, const SDL_Rect& levelsButton, const SDL_Rect& quitButton) {
    if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
        int x = e.button.x;
        int y = e.button.y;

        if (x >= newGameButton.x && x <= newGameButton.x + newGameButton.w &&
            y >= newGameButton.y && y <= newGameButton.y + newGameButton.h) {
            selectedOption = 0; // New Game
        }

        else if (x >= settingsButton.x && x <= settingsButton.x + settingsButton.w &&
                 y >= settingsButton.y && y <= settingsButton.y + settingsButton.h) {
            selectedOption = 2; // Settings
        }
        else if (x >= levelsButton.x && x <= levelsButton.x + levelsButton.w &&
                 y >= levelsButton.y && y <= levelsButton.y + levelsButton.h) {
            selectedOption = 1; // Levels
        }
        else if (x >= quitButton.x && x <= quitButton.x + quitButton.w &&
                 y >= quitButton.y && y <= quitButton.y + quitButton.h) {
            selectedOption = 3; // Quit
        }
    }
}

int Menu::getSelectedOption() const {
    return selectedOption;
}
