#include "Snake.h"
#include <SDL2/SDL_image.h>
#include <iostream>

Snake::Snake(SDL_Renderer* renderer) : dx(20), dy(0) {

    SDL_Rect head = {320, 240, 20, 20};
    body.push_back(head);
    directions.push_back({dx, dy});

    SDL_Rect bodySegment1 = head;
    bodySegment1.x -= dx;
    bodySegment1.y -= dy;
    body.push_back(bodySegment1);
    directions.push_back({dx, dy});

    SDL_Rect bodySegment2 = bodySegment1;
    bodySegment2.x -= dx;
    bodySegment2.y -= dy;
    body.push_back(bodySegment2);
    directions.push_back({dx, dy});

    headTexture = IMG_LoadTexture(renderer, "assets/images/head.png");
    bodyTexture = IMG_LoadTexture(renderer, "assets/images/body.png");
    tailTexture = IMG_LoadTexture(renderer, "assets/images/tail.png");

    if (!headTexture) std::cerr << "Không tải được head.png: " << SDL_GetError() << std::endl;
    if (!bodyTexture) std::cerr << "Không tải được body.png: " << SDL_GetError() << std::endl;
    if (!tailTexture) std::cerr << "Không tải được tail.png: " << SDL_GetError() << std::endl;
}

Snake::~Snake() {
    SDL_DestroyTexture(headTexture);
    SDL_DestroyTexture(bodyTexture);
    SDL_DestroyTexture(tailTexture);
}

void Snake::update(bool ateFood) {
    SDL_Rect newHead = body[0];
    newHead.x += dx;
    newHead.y += dy;

    //xu li ra ngoai man hinh
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
    directions.insert(directions.begin(), {dx, dy});

    if (!ateFood) {
        body.pop_back();
        directions.pop_back();
    }
}

void Snake::render(SDL_Renderer* renderer) {
    for (size_t i = 0; i < body.size(); ++i) {
        SDL_Texture* texture = bodyTexture;
        double angle = 0.0;
        //xac dinh goc quay
        if (i == 0) {
            texture = headTexture;
            if (dx == 20 && dy == 0) angle = 0;
            else if (dx == -20 && dy == 0) angle = 180;
            else if (dx == 0 && dy == -20) angle = 270;
            else if (dx == 0 && dy == 20) angle = 90;
        } else if (i == body.size() - 1) {
            texture = tailTexture;
            auto [tailDx, tailDy] = directions[i];
            if (tailDx == 20 && tailDy == 0) angle = 0;
            else if (tailDx == -20 && tailDy == 0) angle = 180;
            else if (tailDx == 0 && tailDy == -20) angle = 270;
            else if (tailDx == 0 && tailDy == 20) angle = 90;
        } else {

            auto [bodyDx, bodyDy] = directions[i];
            if (bodyDx == 20 && bodyDy == 0) angle = 0;
            else if (bodyDx == -20 && bodyDy == 0) angle = 180;
            else if (bodyDx == 0 && bodyDy == -20) angle = 270;
            else if (bodyDx == 0 && bodyDy == 20) angle = 90;
        }

        if (!texture) {
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            SDL_RenderFillRect(renderer, &body[i]);
        } else {
            SDL_RenderCopyEx(renderer, texture, nullptr, &body[i], angle, nullptr, SDL_FLIP_NONE);
        }
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

const std::vector<SDL_Rect>& Snake::getBody() const {
    return body;
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
