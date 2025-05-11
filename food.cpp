#include "Food.h"
#include <cstdlib>
#include <ctime>

Food::Food() {

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    spawn();
}

void Food::spawn() {

    foodRect.w = 20;
    foodRect.h = 20;
    foodRect.x = (std::rand() % (1280 / 20)) * 20;
    foodRect.y = (std::rand() % (720 / 20)) * 20;
}

void Food::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &foodRect);
}

SDL_Rect Food::getRect()const {
    return foodRect;
}
