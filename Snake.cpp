#include "Snake.h"

Snake::Snake() {

    SDL_Rect head = {320, 240, 20, 20};
    body.push_back(head);


    dx = 20;
    dy = 0;
}

void Snake::update(bool ateFood) {

    SDL_Rect newHead = body[0];
    newHead.x += dx;
    newHead.y += dy;

    //update vi tri ran sau khi di qua khung hinh
    const int SCREEN_WIDTH = 1280;
    const int SCREEN_HEIGHT = 720;
    if (newHead.x >= SCREEN_WIDTH) {
        newHead.x = 0;
    } else if (newHead.x + newHead.w <= 0) {
        newHead.x = SCREEN_WIDTH - newHead.w;
    }
    if (newHead.y >= SCREEN_HEIGHT) {
        newHead.y = 0;
    } else if (newHead.y + newHead.h <= 0) {
        newHead.y = SCREEN_HEIGHT - newHead.h;
    }

    body.insert(body.begin(), newHead);

    // neu chua an duoc moi thi xoa phan duoi
    if (!ateFood) {
        body.pop_back();
    }

}

void Snake::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
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

SDL_Rect Snake::getHead() const {
    return body.front();
}
bool Snake::isSelfCollision() const {
    const SDL_Rect& head = body.front();
    for (size_t i = 1; i < body.size(); ++i) {
        if (SDL_HasIntersection(&head, &body[i])) {
            return true;
        }
    }
    return false;
}

