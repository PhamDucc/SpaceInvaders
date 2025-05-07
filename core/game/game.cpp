#include "D:\Space Invaders\core\game\game.h"

void runGame(SDL_Window* window, SDL_Renderer* renderer) {
    if (!showMenu(renderer)) {
        return; 
    }

    SDL_Texture* bgTexture = loadTexture("assets/background.png", renderer);
    if (!bgTexture) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    Ship ship;
    initializeShip(ship, renderer);

    SDL_Texture* firstAlienTexture = loadTexture("assets/thefirstalien.png", renderer);
    SDL_Texture* secondAlienTexture = loadTexture("assets/thesecondalien.png", renderer);
    SDL_Texture* thirdAlienTexture = loadTexture("assets/thethirdalien.png", renderer);
    SDL_Texture* bulletTexture = loadTexture("assets/bullet.png", renderer);
    SDL_Texture* alienBulletTexture = loadTexture("assets/alienbullet.png", renderer);
    SDL_Texture* heartTexture = loadTexture("assets/heart.png", renderer);

    if (!firstAlienTexture || !secondAlienTexture || !thirdAlienTexture || !bulletTexture || !alienBulletTexture || !heartTexture) {
        SDL_DestroyTexture(bgTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    bool aliensExhausted = false;
    bool quit = false;
    SDL_Event e;

    bool moveLeft = false;
    bool moveRight = false;

    float alienX = 0;
    float alienY = 0;
    bool moveRightAliens = true;

    auto lastMoveTime = std::chrono::high_resolution_clock::now();
    auto lastAlienShootTime = std::chrono::high_resolution_clock::now();

    Bullet shipBullet = {0, 0, false};
    std::vector<Bullet> alienBullets;
    std::vector<Alien> aliens;

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

        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float, std::milli> elapsed = currentTime - lastMoveTime;
        std::chrono::duration<float> alienShootElapsed = currentTime - lastAlienShootTime;

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
                        showGameOverScreen(renderer);
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
            showYouWinScreen(renderer);
            quit = true;
        }

        moveBullet(shipBullet);

        if (!aliensExhausted) {
            checkBulletCollision(shipBullet, aliens);
        }

        for (const auto& alien : aliens) {
            if (alien.active && ship.x < alien.x + ALIEN_WIDTH && ship.x + SHIP_WIDTH > alien.x &&
                ship.y < alien.y + ALIEN_HEIGHT && ship.y + SHIP_HEIGHT > alien.y) {
                showGameOverScreen(renderer);
                quit = true;
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
}