#include "D:\Space Invaders\menu\menu.h"

using namespace std;

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

void showGameOverScreen(SDL_Renderer* renderer) {
    SDL_Texture* gameOverTexture = loadTexture("assets/gameover.png", renderer);
    if (!gameOverTexture) {
        SDL_Log("Failed to load gameover.png!");
        return;
    }

    auto startTime = chrono::high_resolution_clock::now();
    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        auto currentTime = chrono::high_resolution_clock::now();
        chrono::duration<float> elapsed = currentTime - startTime;

        if (elapsed.count() >= 8.0f) { 
            quit = true;
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, gameOverTexture, nullptr, nullptr);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(gameOverTexture);
}

void showYouWinScreen(SDL_Renderer* renderer) {
    SDL_Texture* youWinTexture = loadTexture("assets/youwin.png", renderer);
    if (!youWinTexture) {
        SDL_Log("Failed to load youwin.png!");
        return;
    }

    auto startTime = chrono::high_resolution_clock::now();
    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        auto currentTime = chrono::high_resolution_clock::now();
        chrono::duration<float> elapsed = currentTime - startTime;

        if (elapsed.count() >= 8.0f) { 
            quit = true;
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, youWinTexture, nullptr, nullptr);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(youWinTexture);
}

bool showMenu(SDL_Renderer* renderer) {
    bool quit = false;
    bool startGame = false;
    SDL_Event e;

    SDL_Texture* bgTexture = loadTexture("assets/outsidebackground.png", renderer);
    if (!bgTexture) {
        SDL_Log("Failed to load menu background image!");
        return false;
    }

    SDL_Rect startButton = {SCREEN_WIDTH - 660, SCREEN_HEIGHT - 70, 330, 45};

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    quit = true;
                } else if (e.key.keysym.sym == SDLK_RETURN) {
                    startGame = true;
                    quit = true;
                }
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX = e.button.x;
                int mouseY = e.button.y;

                if (mouseX >= startButton.x && mouseX <= startButton.x + startButton.w &&
                    mouseY >= startButton.y && mouseY <= startButton.y + startButton.h) {
                    startGame = true;
                    quit = true;
                }
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, bgTexture, nullptr, nullptr);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &startButton);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(bgTexture);
    return startGame;
}
