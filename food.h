#ifndef FOOD_H
#define FOOD_H

#include <SDL2/SDL.h>

class Food {
public:
    Food();
    void spawn();                    // Tạo mồi ở vị trí ngẫu nhiên
    void render(SDL_Renderer* renderer); // Vẽ mồi lên màn hình
    SDL_Rect getRect() const;       // Lấy vị trí mồi

private:
    SDL_Rect rect; // Hình chữ nhật đại diện cho mồi
};

#endif // FOOD_H
