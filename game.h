#pragma once
#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include "Snake.h"
#include "Food.h"

class Game {
public:
    Game(SDL_Renderer* renderer, int mode = 0);
    ~Game();
    void startNewGame(SDL_Renderer* renderer, int delayMs);
    bool isPaused() const;
    bool isExitToMenu() const;

private:
    Snake snake;
    Food food;
    Food specialFood;
    bool specialFoodActive;
    Uint32 specialFoodSpawnTime;
    Uint32 lastSpecialFoodTime;
    int score;
    int highScore;
    bool paused;
    bool exitToMenu;
    SDL_Renderer* renderer;
    SDL_Texture* notificationTexture;
    SDL_Rect notificationRect;
    SDL_Texture* backgroundTexture;
    int gameMode;
    int currentDelayMs;
    Uint32 lastSpeedChangeTime;
    TTF_Font* font;
    SDL_Texture* scoreTexture;
    SDL_Rect scoreRect;
    SDL_Texture* gameOverTexture; // Texture cho khung game over (score.png)
    SDL_Rect gameOverRect; // Vị trí khung game over
    SDL_Texture* gameOverScoreTexture; // Texture cho điểm và điểm cao trong khung
    SDL_Rect gameOverScoreRect; // Vị trí hiển thị điểm trong khung
    bool gameOver; // Trạng thái game over

    // Biến mới cho settings
    SDL_Texture* reverseSnakeTexture; // Texture cho reverse_snake.png
    SDL_Texture* tickTexture; // Texture cho tick.png
    SDL_Rect reverseSnakeRect; // Vị trí khung reverse_snake
    bool reverseMode; // Trạng thái reverse mode (true nếu được chọn)

    void updateScoreTexture();
    void loadHighScore();
    void saveHighScore();
    void showGameOverScreen(); // Hiển thị bảng game over
};
