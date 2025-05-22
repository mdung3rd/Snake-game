#pragma once
#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include "Snake.h"
#include "Food.h"

class Game {
public:
    Game(SDL_Renderer* renderer, int mode = 0, bool reverseMode = false);
    ~Game();
    void startNewGame(SDL_Renderer* renderer, int delayMs);
    bool isPaused() const;
    bool isExitToMenu() const;
    void setReverseMode(bool mode); // Thêm phương thức để cập nhật reverseMode

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
    SDL_Texture* gameOverTexture;
    SDL_Rect gameOverRect;
    SDL_Texture* gameOverScoreTexture;
    SDL_Rect gameOverScoreRect;
    bool gameOver;

    SDL_Texture* reverseSnakeTexture;
    SDL_Texture* tickTexture;
    SDL_Rect reverseSnakeRect;
    bool reverseMode;

    void updateScoreTexture();
    void loadHighScore();
    void saveHighScore();
    void showGameOverScreen();
};
