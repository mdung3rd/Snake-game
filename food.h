#ifndef FOOD_H
#define FOOD_H

#include <SDL2/SDL.h>

class Food {
public:
    Food();
    void spawn();
    void render(SDL_Renderer* renderer, bool isSpecial = false) const;
    SDL_Rect getRect() const;

private:
    SDL_Rect foodRect;
};

#endif
