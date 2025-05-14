#ifndef MENU_H
#define MENU_H
#include <SDL2/SDL.h>

class Menu {
public:
    Menu();
    void handleEvent(const SDL_Event& e, const SDL_Rect& newGameButton, const SDL_Rect& settingsButton, const SDL_Rect& levelsButton, const SDL_Rect& quitButton);
    int getSelectedOption() const;

private:
    int selectedOption; // 0: New Game, 1: Levels, 2: Settings, 3: Quit, -1: None
};

#endif
