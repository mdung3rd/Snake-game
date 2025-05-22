#include "Game.h"
#include "Snake.h"
#include "Food.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include "Menu.h"

Game::Game(SDL_Renderer* renderer, int mode, bool reverseMode): snake(renderer), food(renderer), specialFood(renderer), specialFoodActive(false), score(0), highScore(0), paused(false), exitToMenu(false), renderer(renderer), gameMode(mode), currentDelayMs(0), lastSpeedChangeTime(0), font(nullptr), scoreTexture(nullptr), gameOverTexture(nullptr), gameOverScoreTexture(nullptr), gameOver(false), reverseSnakeTexture(nullptr), tickTexture(nullptr), reverseMode(reverseMode) {
    food.spawn();
    lastSpecialFoodTime = SDL_GetTicks();
    lastSpeedChangeTime = SDL_GetTicks();
    srand(static_cast<unsigned int>(time(nullptr)));

    if (TTF_Init() == -1) {
        std::cerr << "Khong khoi tao duoc SDL_ttf: " << TTF_GetError() << std::endl;
        throw std::runtime_error("failed SDL_ttf");
    }

    font = TTF_OpenFont("assets/fonts/baloo2.ttf", 24);
    if (!font) {
        std::cerr << "Khong tai duoc font: " << TTF_GetError() << std::endl;
        throw std::runtime_error("load font lỗi");
    }

    loadHighScore();
    updateScoreTexture();
    scoreRect = {10, 10, 0, 0};

    notificationTexture = IMG_LoadTexture(renderer, "assets/images/notification2.png");
    if (!notificationTexture) {
        std::cerr << "khong tai duoc thong bao 2 " << SDL_GetError() << std::endl;
    }
    notificationRect = {640 - 150, 50, 300, 80};

    backgroundTexture = IMG_LoadTexture(renderer, "assets/images/backgroundingame.png");
    if (!backgroundTexture) {
        std::cerr << "khong tai duoc background texture " << SDL_GetError() << std::endl;
    }

    gameOverTexture = IMG_LoadTexture(renderer, "assets/images/score.png");
    if (!gameOverTexture) {
        std::cerr << "khong tai duoc score.png: " << SDL_GetError() << std::endl;
    }

    reverseSnakeTexture = IMG_LoadTexture(renderer, "assets/images/reverse_snake.png");
    if (!reverseSnakeTexture) {
        std::cerr << "khong tai duoc reverse_snake.png: " << SDL_GetError() << std::endl;
    }

    tickTexture = IMG_LoadTexture(renderer, "assets/images/tick.png");
    if (!tickTexture) {
        std::cerr << "khong tai duoc tick.png: " << SDL_GetError() << std::endl;
    }

    gameOverRect = {1280 / 2 - 150, 720 / 2 - 50, 300, 100};
    reverseSnakeRect = {1280 / 2 - 150, 720 / 2 - 50, 300, 100};
}

Game::~Game() {
    saveHighScore();
    if (notificationTexture) SDL_DestroyTexture(notificationTexture);
    if (backgroundTexture) SDL_DestroyTexture(backgroundTexture);
    if (scoreTexture) SDL_DestroyTexture(scoreTexture);
    if (gameOverTexture) SDL_DestroyTexture(gameOverTexture);
    if (gameOverScoreTexture) SDL_DestroyTexture(gameOverScoreTexture);
    if (font) TTF_CloseFont(font);
    if (reverseSnakeTexture) SDL_DestroyTexture(reverseSnakeTexture);
    if (tickTexture) SDL_DestroyTexture(tickTexture);
    TTF_Quit();
}

void Game::updateScoreTexture() {
    if (!font) return;
    std::stringstream ss;
    ss << "Score: " << score;
    std::string scoreText = ss.str();
    SDL_Color textColor = {139, 69, 19, 255};
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreText.c_str(), textColor);
    if (!textSurface) {
        std::cerr << "Khong tao duoc text surface: " << TTF_GetError() << std::endl;
        return;
    }
    if (scoreTexture) SDL_DestroyTexture(scoreTexture);
    scoreTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!scoreTexture) {
        std::cerr << "Khong tao duoc score texture: " << SDL_GetError() << std::endl;
    }
    scoreRect.w = textSurface->w;
    scoreRect.h = textSurface->h;
    SDL_FreeSurface(textSurface);
}

void Game::loadHighScore() {
    std::ifstream file("highscore.txt");
    if (file.is_open()) {
        file >> highScore;
        file.close();
    } else {
        highScore = 0;
    }
}

void Game::saveHighScore() {
    if (score > highScore) {
        highScore = score;
        std::ofstream file("highscore.txt");
        if (file.is_open()) {
            file << highScore;
            file.close();
        }
    }
}

void Game::showGameOverScreen() {
    if (!font) {
        std::cerr << "Khong the hien thi game over: Font khong ton tai!" << std::endl;
        return;
    }
    std::stringstream ss;
    ss << "Score: " << score;
    std::string gameOverText = ss.str();
    SDL_Color textColor = {139, 69, 19, 255};
    SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(font, gameOverText.c_str(), textColor, gameOverRect.w - 20);
    if (!textSurface) {
        std::cerr << "Khong tao duoc game over text surface: " << TTF_GetError() << std::endl;
        return;
    }
    if (gameOverScoreTexture) SDL_DestroyTexture(gameOverScoreTexture);
    gameOverScoreTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!gameOverScoreTexture) {
        std::cerr << "Khong tao duoc game over score texture: " << SDL_GetError() << std::endl;
    }
    gameOverScoreRect.x = gameOverRect.x + 10;
    gameOverScoreRect.y = gameOverRect.y + (gameOverRect.h - textSurface->h) / 2;
    gameOverScoreRect.w = textSurface->w;
    gameOverScoreRect.h = textSurface->h;
    SDL_FreeSurface(textSurface);

    bool waitingForExit = true;
    SDL_Event e;
    while (waitingForExit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                waitingForExit = false;
                exitToMenu = true;
            } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
                waitingForExit = false;
                exitToMenu = true;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        if (backgroundTexture) SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
        snake.render(renderer);
        food.render(renderer);
        if (specialFoodActive) specialFood.render(renderer, true);
        if (scoreTexture) SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
        if (gameOverTexture) SDL_RenderCopy(renderer, gameOverTexture, NULL, &gameOverRect);
        if (gameOverScoreTexture) SDL_RenderCopy(renderer, gameOverScoreTexture, NULL, &gameOverScoreRect);
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }
}

void Game::setReverseMode(bool mode) {
    reverseMode = mode;
}

void Game::startNewGame(SDL_Renderer* renderer, int delayMs) {
    currentDelayMs = delayMs;
    bool running = true;
    SDL_Event e;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            } else if (e.type == SDL_KEYDOWN) {
                if (!paused) {
                    snake.changeDirection(e.key.keysym.sym, reverseMode);
                }
                switch (e.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        paused = true;
                        break;
                    case SDLK_y:
                        if (paused) {
                            exitToMenu = true;
                            running = false;
                        }
                        break;
                    case SDLK_n:
                        if (paused) {
                            paused = false;
                        }
                        break;
                }
            }
        }
        if (!paused) {
            Uint32 currentTime = SDL_GetTicks();
            if (gameMode == 2 && (currentTime - lastSpeedChangeTime) >= 2000) {
                currentDelayMs = 50 + (rand() % 101);
                std::cout << "Special Mode: Speed changed! Current delay: " << currentDelayMs << "ms" << std::endl;
                lastSpeedChangeTime = currentTime;
            }
            if (currentTime - lastSpecialFoodTime >= 15000 && !specialFoodActive) {
                specialFood.spawn();
                specialFoodActive = true;
                specialFoodSpawnTime = currentTime;
                lastSpecialFoodTime = currentTime;
            }
            if (specialFoodActive && currentTime - specialFoodSpawnTime >= 7000) {
                specialFoodActive = false;
            }
            SDL_Rect head = snake.getHead();
            SDL_Rect foodRect = food.getRect();
            SDL_Rect specialFoodRect = specialFood.getRect();
            bool ateFood = SDL_HasIntersection(&head, &foodRect);
            bool ateSpecialFood = specialFoodActive && SDL_HasIntersection(&head, &specialFoodRect);
            if (ateFood) {
                score += 1;
                food.spawn();
                snake.update(true);
                updateScoreTexture();
            }
            if (ateSpecialFood) {
                score += (gameMode == 0 ? 4 : gameMode == 1 ? 6 : 8);
                for (int i = 0; i < 4; ++i) {
                    snake.update(true);
                }
                specialFoodActive = false;
                updateScoreTexture();
            }
            if (!ateFood && !ateSpecialFood) {
                snake.update(false);
            }
            if (snake.isSelfCollision()) {
                std::cout << "Game Over. Score: " << score << std::endl;
                saveHighScore();
                gameOver = true;
                showGameOverScreen();
                running = false;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        if (backgroundTexture) SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
        snake.render(renderer);
        food.render(renderer);
        if (specialFoodActive) specialFood.render(renderer, true);
        if (scoreTexture) SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
        if (paused && notificationTexture) SDL_RenderCopy(renderer, notificationTexture, NULL, &notificationRect);
        SDL_RenderPresent(renderer);
        SDL_Delay(currentDelayMs);
    }
}

bool Game::isPaused() const {
    return paused;
}

bool Game::isExitToMenu() const {
    return exitToMenu;
}
