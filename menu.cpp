#include "Menu.h"

Menu::Menu() : selectedOption(-1) {
}

void Menu::handleEvent(const SDL_Event& e, const SDL_Rect& newGameButton, const SDL_Rect& settingsButton, const SDL_Rect& levelsButton, const SDL_Rect& quitButton, const SDL_Rect& easyButton, const SDL_Rect& hardButton, const SDL_Rect& specialButton, const SDL_Rect& backButton, bool isLevelsMenuActive, bool isSettingsMenuActive) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int x = e.button.x;
        int y = e.button.y;

        if (!isLevelsMenuActive && !isSettingsMenuActive) {
            if (x >= newGameButton.x && x <= newGameButton.x + newGameButton.w &&
                y >= newGameButton.y && y <= newGameButton.y + newGameButton.h) {
                selectedOption = 0;
            }
            else if (x >= settingsButton.x && x <= settingsButton.x + settingsButton.w &&
                     y >= settingsButton.y && y <= settingsButton.y + settingsButton.h) {
                selectedOption = 2;
            }
            else if (x >= levelsButton.x && x <= levelsButton.x + levelsButton.w &&
                     y >= levelsButton.y && y <= levelsButton.y + levelsButton.h) {
                selectedOption = 1;
            }
            else if (x >= quitButton.x && x <= quitButton.x + quitButton.w &&
                     y >= quitButton.y && y <= quitButton.y + quitButton.h) {
                selectedOption = 3;
            }
        } else {
            if (x >= easyButton.x && x <= easyButton.x + easyButton.w &&
                y >= easyButton.y && y <= easyButton.y + easyButton.h) {
                selectedOption = 10; // ez
            }
            else if (x >= hardButton.x && x <= hardButton.x + hardButton.w &&
                     y >= hardButton.y && y <= hardButton.y + hardButton.h) {
                selectedOption = 11; //hard
            }
            else if (x >= specialButton.x && x <= specialButton.x + specialButton.w &&
                     y >= specialButton.y && y <= specialButton.y + specialButton.h) {
                selectedOption = 12; // spec
            }
            else if (x >= backButton.x && x <= backButton.x + backButton.w &&
                     y >= backButton.y && y <= backButton.y + backButton.h) {
                selectedOption = 4; // back
            }
        }
    }
}

int Menu::getSelectedOption() const {
    return selectedOption;
}
