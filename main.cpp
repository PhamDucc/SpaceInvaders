#include "src/include/SDL2/SDL.h"
#include "src/include/SDL2/SDL_image.h"
#include "src/include/SDL2/SDL_ttf.h"
#include "game/ship/ship.h"
#include "game/alien/alien.h"
#include "game/shipbullet/shipbullet.h"

#include <iostream>
#include <chrono>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

#undef main

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 700;

const int ALIEN_BULLET_WIDTH = 35; 
const int ALIEN_BULLET_HEIGHT = 25; 
const float ALIEN_BULLET_SPEED = 0.15f; 

SDL_Texture* heartTexture = nullptr;

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        return 1;
    }

    if (TTF_Init() == -1) {
        cerr << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() << endl;
        SDL_Quit();
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000, 700, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        cerr << "SDL_image không thể khởi tạo! Lỗi SDL_image: " << IMG_GetError() << endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Surface* bgSurface = IMG_Load("assets/background.png");
    if (bgSurface == nullptr) {
        cerr << "Không thể tải ảnh! Lỗi SDL_image: " << IMG_GetError() << endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Texture* bgTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
    SDL_FreeSurface(bgSurface);
    if (bgTexture == nullptr) {
        cerr << "Không thể tạo texture từ surface! Lỗi SDL: " << SDL_GetError() << endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    Ship ship;
    initializeShip(ship, renderer);

    SDL_Surface* firstAlienSurface = IMG_Load("assets/thefirstalien.png");
    if (firstAlienSurface == nullptr) {
        cerr << "Không thể tải ảnh thefirstalien! Lỗi SDL_image: " << IMG_GetError() << endl;
        SDL_DestroyTexture(ship.texture);
        SDL_DestroyTexture(bgTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Texture* firstAlienTexture = SDL_CreateTextureFromSurface(renderer, firstAlienSurface);
    SDL_FreeSurface(firstAlienSurface);
    if (firstAlienTexture == nullptr) {
        cerr << "Không thể tạo texture từ surface thefirstalien! Lỗi SDL: " << SDL_GetError() << endl;
        SDL_DestroyTexture(ship.texture);
        SDL_DestroyTexture(bgTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Surface* secondAlienSurface = IMG_Load("assets/thesecondalien.png");
    if (secondAlienSurface == nullptr) {
        cerr << "Không thể tải ảnh thesecondalien! Lỗi SDL_image: " << IMG_GetError() << endl;
        SDL_DestroyTexture(firstAlienTexture);
        SDL_DestroyTexture(ship.texture);
        SDL_DestroyTexture(bgTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Texture* secondAlienTexture = SDL_CreateTextureFromSurface(renderer, secondAlienSurface);
    SDL_FreeSurface(secondAlienSurface);
    if (secondAlienTexture == nullptr) {
        cerr << "Không thể tạo texture từ surface thesecondalien! Lỗi SDL: " << SDL_GetError() << endl;
        SDL_DestroyTexture(firstAlienTexture);
        SDL_DestroyTexture(ship.texture);
        SDL_DestroyTexture(bgTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Surface* thirdAlienSurface = IMG_Load("assets/thethirdalien.png");
    if (thirdAlienSurface == nullptr) {
        cerr << "Không thể tải ảnh thethirdalien! Lỗi SDL_image: " << IMG_GetError() << endl;
        SDL_DestroyTexture(secondAlienTexture);
        SDL_DestroyTexture(firstAlienTexture);
        SDL_DestroyTexture(ship.texture);
        SDL_DestroyTexture(bgTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Texture* thirdAlienTexture = SDL_CreateTextureFromSurface(renderer, thirdAlienSurface);
    SDL_FreeSurface(thirdAlienSurface);
    if (thirdAlienTexture == nullptr) {
        cerr << "Không thể tạo texture từ surface thethirdalien! Lỗi SDL: " << SDL_GetError() << endl;
        SDL_DestroyTexture(secondAlienTexture);
        SDL_DestroyTexture(firstAlienTexture);
        SDL_DestroyTexture(ship.texture);
        SDL_DestroyTexture(bgTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Surface* bulletSurface = IMG_Load("assets/bullet.png");
    if (bulletSurface == nullptr) {
        cerr << "Không thể tải ảnh bullet! Lỗi SDL_image: " << IMG_GetError() << endl;
        SDL_DestroyTexture(thirdAlienTexture);
        SDL_DestroyTexture(secondAlienTexture);
        SDL_DestroyTexture(firstAlienTexture);
        SDL_DestroyTexture(ship.texture);
        SDL_DestroyTexture(bgTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Texture* bulletTexture = SDL_CreateTextureFromSurface(renderer, bulletSurface);
    SDL_FreeSurface(bulletSurface);
    if (bulletTexture == nullptr) {
        cerr << "Không thể tạo texture từ surface bullet! Lỗi SDL: " << SDL_GetError() << endl;
        SDL_DestroyTexture(thirdAlienTexture);
        SDL_DestroyTexture(secondAlienTexture);
        SDL_DestroyTexture(firstAlienTexture);
        SDL_DestroyTexture(ship.texture);
        SDL_DestroyTexture(bgTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Surface* alienBulletSurface = IMG_Load("assets/alienbullet.png");
    if (alienBulletSurface == nullptr) {
        cerr << "Không thể tải ảnh alienbullet! Lỗi SDL_image: " << IMG_GetError() << endl;
        SDL_DestroyTexture(thirdAlienTexture);
        SDL_DestroyTexture(secondAlienTexture);
        SDL_DestroyTexture(firstAlienTexture);
        SDL_DestroyTexture(ship.texture);
        SDL_DestroyTexture(bgTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Texture* alienBulletTexture = SDL_CreateTextureFromSurface(renderer, alienBulletSurface);
    SDL_FreeSurface(alienBulletSurface);
    if (alienBulletTexture == nullptr) {
        cerr << "Không thể tạo texture từ surface alienbullet! Lỗi SDL: " << SDL_GetError() << endl;
        SDL_DestroyTexture(thirdAlienTexture);
        SDL_DestroyTexture(secondAlienTexture);
        SDL_DestroyTexture(firstAlienTexture);
        SDL_DestroyTexture(ship.texture);
        SDL_DestroyTexture(bgTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Load heart texture
    SDL_Surface* heartSurface = IMG_Load("assets/heart.png");
    if (heartSurface == nullptr) {
        cerr << "Không thể tải ảnh trái tim! Lỗi SDL_image: " << IMG_GetError() << endl;
        exit(1);
    }
    heartTexture = SDL_CreateTextureFromSurface(renderer, heartSurface);
    SDL_FreeSurface(heartSurface);
    if (heartTexture == nullptr) {
        cerr << "Không thể tạo texture từ surface trái tim! Lỗi SDL: " << SDL_GetError() << endl;
        exit(1);
    }

    bool quit = false;
    SDL_Event e;

    bool moveLeft = false;
    bool moveRight = false;

    float alienX = 0;
    float alienY = 0;
    bool moveRightAliens = true;

    auto lastMoveTime = chrono::high_resolution_clock::now();
    auto lastAlienShootTime = chrono::high_resolution_clock::now();
    auto lastShipShootTime = chrono::high_resolution_clock::now();
    srand(static_cast<unsigned>(time(0)));

    Bullet shipBullet = {0, 0, false}; // Single bullet for the ship
    vector<Bullet> alienBullets; 
    vector<Alien> aliens;

    initializeAliens(aliens, alienX, alienY);

    int respawnCount = 0;

    SDL_StartTextInput();

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_a:
                        moveLeft = true;
                        break;
                    case SDLK_d:
                        moveRight = true;
                        break;
                    case SDLK_SPACE:
                        createBullet(shipBullet, ship.x, ship.y); // Ensure only one bullet is created
                        break;
                }
            } else if (e.type == SDL_KEYUP) {
                switch (e.key.keysym.sym) {
                    case SDLK_a:
                        moveLeft = false;
                        break;
                    case SDLK_d:
                        moveRight = false;
                        break;
                }
            }
        }

        moveShip(ship, moveLeft, moveRight);

        auto currentTime = chrono::high_resolution_clock::now();
        chrono::duration<float, milli> elapsed = currentTime - lastMoveTime;
        chrono::duration<float> alienShootElapsed = currentTime - lastAlienShootTime;

        if (elapsed.count() >= ALIEN_DELAY) {
            if (moveRightAliens) {
                alienX += ALIEN_SPEED;
                if (alienX + 10 * (ALIEN_WIDTH + ALIEN_SPACING) > SCREEN_WIDTH) {
                    moveRightAliens = false;
                    alienY += ALIEN_HEIGHT + ALIEN_SPACING;
                }
            } else {
                alienX -= ALIEN_SPEED;
                if (alienX < 0) {
                    moveRightAliens = true;
                    alienY += ALIEN_HEIGHT + ALIEN_SPACING;
                }
            }
            lastMoveTime = currentTime;

            // Update alien positions
            updateAlienPositions(aliens, alienX, alienY);
        }

        // Make thethirdalien shoot bullets randomly
        if (alienShootElapsed.count() >= 3 + rand() % 3) {
            int randomAlienIndex = rand() % 10;
            if (aliens[randomAlienIndex].active) {
                alienBullets.push_back({aliens[randomAlienIndex].x + ALIEN_WIDTH / 2 - ALIEN_BULLET_WIDTH / 2, aliens[randomAlienIndex].y + ALIEN_HEIGHT, true, true});
            }
            lastAlienShootTime = currentTime;
        }

        // Move alien bullets
        for (auto& bullet : alienBullets) {
            if (bullet.active) {
                bullet.y += ALIEN_BULLET_SPEED;
                if (bullet.y > SCREEN_HEIGHT) {
                    bullet.active = false;
                }
            }
        }

        bool allAliensDestroyed = true;
        for (auto& bullet : alienBullets) {
            if (bullet.active && !bullet.isAlienBullet) {
                for (auto& alien : aliens) {
                    if (alien.active && bullet.x < alien.x + ALIEN_WIDTH && bullet.x + BULLET_WIDTH > alien.x &&
                        bullet.y < alien.y + ALIEN_HEIGHT && bullet.y + BULLET_HEIGHT > alien.y) {
                        bullet.active = false;
                        alien.health--;
                        if (alien.health <= 0) {
                            alien.active = false;
                        }
                        break;
                    }
                }
                if (bullet.y < 0) {
                    bullet.active = false;
                }
            }
        }

        for (auto& bullet : alienBullets) {
            if (bullet.active && bullet.isAlienBullet) {
                if (bullet.x < ship.x + SHIP_WIDTH && bullet.x + ALIEN_BULLET_WIDTH > ship.x &&
                    bullet.y < ship.y + SHIP_HEIGHT && bullet.y + ALIEN_BULLET_HEIGHT > ship.y) {
                    bullet.active = false;
                    ship.lives--;
                    if (ship.lives <= 0) {
                        quit = true; 
                    }
                }
            }
        }

        allAliensDestroyed = true;
        for (const auto& alien : aliens) {
            if (alien.active) {
                allAliensDestroyed = false;
                break;
            }
        }
        // Respawn aliens if all are destroyed
        if (allAliensDestroyed) {
            if (respawnCount < 2) {
                float lastAlienX = alienX;
                float lastAlienY = alienY;
                initializeAliens(aliens, lastAlienX, lastAlienY);
                respawnCount++;
            }
        }

        // Move the single ship bullet
        moveBullet(shipBullet);

        // Check for collisions with aliens
        checkBulletCollision(shipBullet, aliens); // Ensure aliens is passed correctly

        // Check for collisions and handle ship hit
        for (const auto& bullet : alienBullets) {
            if (bullet.active && bullet.isAlienBullet &&
                bullet.x < ship.x + SHIP_WIDTH && bullet.x + ALIEN_BULLET_WIDTH > ship.x &&
                bullet.y < ship.y + SHIP_HEIGHT && bullet.y + ALIEN_BULLET_HEIGHT > ship.y) {
                handleShipHit(ship); // Reduce ship lives
                break; // Exit loop after handling the hit
            }
        }

        SDL_RenderClear(renderer); 
        SDL_RenderCopy(renderer, bgTexture, nullptr, nullptr);

        renderShip(ship, renderer);

        // Render the single ship bullet
        renderBullet(shipBullet, renderer, bulletTexture);

        // Render alien bullets
        for (const auto& bullet : alienBullets) {
            if (bullet.active) {
                SDL_Rect bulletRect = { static_cast<int>(bullet.x), static_cast<int>(bullet.y), ALIEN_BULLET_WIDTH, ALIEN_BULLET_HEIGHT };
                SDL_RenderCopy(renderer, alienBulletTexture, nullptr, &bulletRect);
            }
        }

        // Render aliens
        renderAliens(aliens, renderer, firstAlienTexture, secondAlienTexture, thirdAlienTexture);

        // Render hearts
        renderHearts(ship, renderer, heartTexture);

        SDL_RenderPresent(renderer); 
    }

    SDL_StopTextInput();

    SDL_DestroyTexture(heartTexture);
    SDL_DestroyTexture(alienBulletTexture);
    SDL_DestroyTexture(bulletTexture);
    SDL_DestroyTexture(thirdAlienTexture);
    SDL_DestroyTexture(secondAlienTexture);
    SDL_DestroyTexture(firstAlienTexture);
    SDL_DestroyTexture(ship.texture);
    SDL_DestroyTexture(bgTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();

    return 0;
}