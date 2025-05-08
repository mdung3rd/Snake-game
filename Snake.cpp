#include "Snake.h"

Snake::Snake() {

    SDL_Rect head = {320, 240, 20, 20};
    body.push_back(head);


    dx = 20;
    dy = 0;
}

void Snake::update() {

    SDL_Rect newHead = body[0];
    newHead.x += dx;
    newHead.y += dy;


    body.insert(body.begin(), newHead);


    body.pop_back();
}

void Snake::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // màu xanh lá cây
    for (SDL_Rect segment : body) {
        SDL_RenderFillRect(renderer, &segment);
    }
}

void Snake::changeDirection(SDL_Keycode key) {

    switch (key) {
        case SDLK_UP:
            if (dy == 0) { dx = 0; dy = -20; }
            break;
        case SDLK_DOWN:
            if (dy == 0) { dx = 0; dy = 20; }
            break;
        case SDLK_LEFT:
            if (dx == 0) { dx = -20; dy = 0; }
            break;
        case SDLK_RIGHT:
            if (dx == 0) { dx = 20; dy = 0; }
            break;
    }
}

