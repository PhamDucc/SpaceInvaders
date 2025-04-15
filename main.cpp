#include "D:\Space Invaders\init.h"
#include "D:\Space Invaders\game\ship\ship.h"
#include "D:\Space Invaders\game\alien\alien.h"
#include "D:\Space Invaders\game\shipbullet\shipbullet.h"
#include "D:\Space Invaders\game\alienbullet\alienbullet.h"
#include <chrono>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

#undef main

SDL_Texture* heartTexture = nullptr;

int main(int argc, char* argv[]) {
    SDL_Window* window = initializeWindow();
    if (!window) return 1;

    SDL_Renderer* renderer = initializeRenderer(window);
    if (!renderer) return 1;

    SDL_Texture* bgTexture = loadTexture("assets/background.png", renderer);
    if (!bgTexture) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    Ship ship;
    initializeShip(ship, renderer);

    SDL_Texture* firstAlienTexture = loadTexture("assets/thefirstalien.png", renderer);
    SDL_Texture* secondAlienTexture = loadTexture("assets/thesecondalien.png", renderer);
    SDL_Texture* thirdAlienTexture = loadTexture("assets/thethirdalien.png", renderer);
    SDL_Texture* bulletTexture = loadTexture("assets/bullet.png", renderer);
    SDL_Texture* alienBulletTexture = loadTexture("assets/alienbullet.png", renderer);
    heartTexture = loadTexture("assets/heart.png", renderer);

    if (!firstAlienTexture || !secondAlienTexture || !thirdAlienTexture || !bulletTexture || !alienBulletTexture || !heartTexture) {
        SDL_DestroyTexture(bgTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    bool aliensExhausted = false;

    bool quit = false;
    SDL_Event e;

    bool moveLeft = false;
    bool moveRight = false;

    float alienX = 0;
    float alienY = 0;
    bool moveRightAliens = true;

    auto lastMoveTime = chrono::high_resolution_clock::now();
    auto lastAlienShootTime = chrono::high_resolution_clock::now();

    Bullet shipBullet = {0, 0, false};
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
                        createBullet(shipBullet, ship.x, ship.y);
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

        if (!aliensExhausted && elapsed.count() >= ALIEN_DELAY) {
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

            updateAlienPositions(aliens, alienX, alienY);
        }

        if (!aliensExhausted && alienShootElapsed.count() >= 3 + rand() % 3) {
            int randomAlienIndex = rand() % 10;
            if (aliens[randomAlienIndex].active) {
                alienBullets.push_back({aliens[randomAlienIndex].x + ALIEN_WIDTH / 2 - ALIEN_BULLET_WIDTH / 2, aliens[randomAlienIndex].y + ALIEN_HEIGHT, true, true});
            }
            lastAlienShootTime = currentTime;
        }

        moveAlienBullets(alienBullets, SCREEN_HEIGHT);

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

        if (allAliensDestroyed && respawnCount < 3 && !aliensExhausted) {
            float lastAlienX = alienX;
            float lastAlienY = alienY;
            initializeAliens(aliens, lastAlienX, lastAlienY);
            respawnCount++;
        }

        if (allAliensDestroyed && respawnCount == 3) {
            aliensExhausted = true;
        }

        moveBullet(shipBullet);

        if (!aliensExhausted) {
            checkBulletCollision(shipBullet, aliens);
        }

        for (const auto& bullet : alienBullets) {
            if (bullet.active && bullet.isAlienBullet &&
                bullet.x < ship.x + SHIP_WIDTH && bullet.x + ALIEN_BULLET_WIDTH > ship.x &&
                bullet.y < ship.y + SHIP_HEIGHT && bullet.y + ALIEN_BULLET_HEIGHT > ship.y) {
                handleShipHit(ship);
                break;
            }
        }

        SDL_RenderClear(renderer); 
        SDL_RenderCopy(renderer, bgTexture, nullptr, nullptr);

        renderShip(ship, renderer);

        renderBullet(shipBullet, renderer, bulletTexture);

        renderAlienBullets(alienBullets, renderer, alienBulletTexture);

        if (!aliensExhausted) {
            renderAliens(aliens, renderer, firstAlienTexture, secondAlienTexture, thirdAlienTexture);
        }

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