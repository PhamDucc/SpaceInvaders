#ifndef ALIEN_H
#define ALIEN_H

#include "D:\Space Invaders\src\include\SDL2\SDL.h"
#include <vector>

struct Alien {
    float x, y;
    bool active;
    int health;
};

extern const int ALIEN_WIDTH;
extern const int ALIEN_HEIGHT;
extern const int ALIEN_SPACING;
extern const float ALIEN_SPEED;
extern const int ALIEN_DELAY;

void initializeAliens(std::vector<Alien>& aliens, float startX, float startY);
void renderAliens(const std::vector<Alien>& aliens, SDL_Renderer* renderer, SDL_Texture* firstAlienTexture, SDL_Texture* secondAlienTexture, SDL_Texture* thirdAlienTexture);
void updateAlienPositions(std::vector<Alien>& aliens, float alienX, float alienY);
void handleAlienCollisions(std::vector<Alien>& aliens, SDL_Renderer* renderer);

#endif