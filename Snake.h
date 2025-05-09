#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <SDL2/SDL.h>

class Snake {
public:
    Snake();
    void update(bool ateFood);
    void render(SDL_Renderer* renderer);
    void changeDirection(SDL_Keycode key);

    SDL_Rect getHead() const;

    const std::vector<SDL_Rect>& getBody() const;

    bool isSelfCollision() const;

private:
    std::vector<SDL_Rect> body;
    int dx, dy;
};

#endif
