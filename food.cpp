#include "Food.h"
#include <SDL2/SDL_image.h>
#include <iostream>
#include <ctime>

Food::Food(SDL_Renderer* renderer) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    spawn();
    foodTexture = nullptr;
    specialFoodTexture = nullptr;
}

Food::~Food() {
}

void Food::spawn() {
    foodRect.w = 20;
    foodRect.h = 20;
    foodRect.x = (std::rand() % (1280 / 20)) * 20;
    foodRect.y = (std::rand() % (720 / 20)) * 20;
}

void drawFilledCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius) {
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x * x + y * y <= radius * radius) {
                SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
            }
        }
    }
}

void Food::render(SDL_Renderer* renderer, bool isSpecial) const {
    SDL_SetRenderDrawColor(renderer, isSpecial ? 0 : 255, 0, isSpecial ? 255 : 0, 255);

    int centerX = foodRect.x + foodRect.w / 2;
    int centerY = foodRect.y + foodRect.h / 2;
    int radius = foodRect.w / 2;
    drawFilledCircle(renderer, centerX, centerY, radius);
}

SDL_Rect Food::getRect() const {
    return foodRect;
}
