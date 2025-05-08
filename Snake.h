#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <SDL2/SDL.h>

class Snake {
public:
    Snake();

    void update();
    void render(SDL_Renderer* renderer);
    void changeDirection(SDL_Keycode key);
private:
    std::vector<SDL_Rect> body;
    int dx, dy;
};

#endif
