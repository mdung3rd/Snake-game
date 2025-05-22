#pragma once
#include <SDL2/SDL.h>
#include <vector>

class Snake {
public:
    Snake(SDL_Renderer* renderer);
    ~Snake();
    void update(bool ateFood);
    void render(SDL_Renderer* renderer);
    void changeDirection(SDL_Keycode key, bool reverseMode);
    SDL_Rect getHead() const;
    const std::vector<SDL_Rect>& getBody() const;
    bool isSelfCollision() const;


private:
    std::vector<SDL_Rect> body;
    std::vector<std::pair<int, int>> directions;
    std::vector<double> angles;
    int dx, dy;
    SDL_Texture* headTexture;
    SDL_Texture* bodyTexture;
    SDL_Texture* tailTexture;
};
