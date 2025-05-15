#ifndef MENU_H
#define MENU_H
#include <SDL2/SDL.h>

class Menu {
public:
    Menu();
    void handleEvent(const SDL_Event& e, const SDL_Rect& newGameButton, const SDL_Rect& settingsButton, const SDL_Rect& levelsButton, const SDL_Rect& quitButton);
    int getSelectedOption() const;

private:
    int selectedOption;
};

#endif
