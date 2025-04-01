#ifndef SHIP_H
#define SHIP_H

#include "src/include/SDL2/SDL.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern const int SHIP_WIDTH;
const int SHIP_HEIGHT = 70;
const float SHIP_SPEED = 0.1f;

struct Ship {
    float x, y;
    int lives;
    SDL_Texture* texture;
};

void initializeShip(Ship& ship, SDL_Renderer* renderer);
void renderShip(const Ship& ship, SDL_Renderer* renderer);
void moveShip(Ship& ship, bool moveLeft, bool moveRight);
void renderHearts(const Ship& ship, SDL_Renderer* renderer, SDL_Texture* heartTexture);
void handleShipHit(Ship& ship);

#endif