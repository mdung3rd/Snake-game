#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <SDL2/SDL.h>

class Snake {
public:
    Snake();

    void update();                         // Di chuyển rắn
    void render(SDL_Renderer* renderer);   // Vẽ rắn
    void changeDirection(SDL_Keycode key); // Đổi hướng

private:
    std::vector<SDL_Rect> body;  // Các đoạn thân rắn
    int dx, dy;                  // Hướng di chuyển (delta x, y)
};

#endif
