#include "D:\Space Invaders\game\ship\ship.h"
#include "D:\Space Invaders\src\include\SDL2\SDL_image.h"
#include <iostream>

using namespace std;

const int SHIP_WIDTH = 70; // Define the value of SHIP_WIDTH

void initializeShip(Ship& ship, SDL_Renderer* renderer) {
    ship.x = (SCREEN_WIDTH - SHIP_WIDTH) / 2;
    ship.y = SCREEN_HEIGHT - SHIP_HEIGHT - 10;
    ship.lives = 3;

    SDL_Surface* shipSurface = IMG_Load("assets/ship.png");
    if (shipSurface == nullptr) {
        cerr << "Không thể tải ảnh tàu vũ trụ! Lỗi SDL_image: " << IMG_GetError() << endl;
        exit(1);
    }

    ship.texture = SDL_CreateTextureFromSurface(renderer, shipSurface);
    SDL_FreeSurface(shipSurface);
    if (ship.texture == nullptr) {
        cerr << "Không thể tạo texture từ surface tàu vũ trụ! Lỗi SDL: " << SDL_GetError() << endl;
        exit(1);
    }
}

void renderShip(const Ship& ship, SDL_Renderer* renderer) {
    SDL_Rect shipRect = { static_cast<int>(ship.x), static_cast<int>(ship.y), SHIP_WIDTH, SHIP_HEIGHT };
    SDL_RenderCopy(renderer, ship.texture, nullptr, &shipRect);
}

void moveShip(Ship& ship, bool moveLeft, bool moveRight) {
    if (moveLeft) {
        ship.x -= SHIP_SPEED;
        if (ship.x < 0) ship.x = 0;
    }
    if (moveRight) {
        ship.x += SHIP_SPEED;
        if (ship.x > SCREEN_WIDTH - SHIP_WIDTH) ship.x = SCREEN_WIDTH - SHIP_WIDTH;
    }
}

void renderHearts(const Ship& ship, SDL_Renderer* renderer, SDL_Texture* heartTexture) {
    for (int i = 0; i < ship.lives; ++i) {
        SDL_Rect heartRect = { 10 + i * 40, SCREEN_HEIGHT - 50, 30, 30 }; // Position hearts
        SDL_RenderCopy(renderer, heartTexture, nullptr, &heartRect);
    }
}

void handleShipHit(Ship& ship) {
    if (ship.lives > 0) {
        ship.lives--; // Reduce lives when hit
    }
    if (ship.lives == 0) {
        // Handle game over logic here if needed
    }
}
