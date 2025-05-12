#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <string>

class Menu {
public:
    Menu();
    void render(SDL_Renderer* renderer);
    void handleEvent(SDL_Event& e);
    int getSelectedOption() const;
    void handleMouseEvent(SDL_Event& e);

private:
    int selectedOption;
    const std::string menuOptions[4] = {"New Game", "Levels", "Settings", "Quit"};
};

#endif

