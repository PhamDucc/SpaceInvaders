#ifndef ALIEN_H
#define ALIEN_H

#include "D:\Space Invaders\src\include\SDL2\SDL.h"
#include <vector>

struct Alien {
    float x, y;
    bool active;
    int health;
};

const int ALIEN_WIDTH = 70;
const int ALIEN_HEIGHT = 60;
const int ALIEN_SPACING = 2;
const float ALIEN_SPEED = 10.0f;
const int ALIEN_DELAY = 750;

void initializeAliens(std::vector<Alien>& aliens, float startX, float startY);
void renderAliens(const std::vector<Alien>& aliens, SDL_Renderer* renderer, SDL_Texture* firstAlienTexture, SDL_Texture* secondAlienTexture, SDL_Texture* thirdAlienTexture);
void updateAlienPositions(std::vector<Alien>& aliens, float alienX, float alienY);
void handleAlienCollisions(std::vector<Alien>& aliens, SDL_Renderer* renderer);

#endif