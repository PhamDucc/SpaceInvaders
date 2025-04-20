#ifndef SHIPBULLET_H
#define SHIPBULLET_H

#include "D:\Space Invaders\src\include\SDL2\SDL.h"
#include <vector>
#include "D:\Space Invaders\objects\alien\alien.h"

extern const int SCREEN_WIDTH; 
extern const int SCREEN_HEIGHT;
extern const int SHIP_WIDTH;
extern const int ALIEN_WIDTH;
extern const int ALIEN_HEIGHT;

const int BULLET_WIDTH = 25;
const int BULLET_HEIGHT = 15;
const float BULLET_SPEED = 0.2f;

struct Bullet {
    float x, y;
    bool active;
    bool isAlienBullet = false;
};

void createBullet(Bullet& shipBullet, float shipX, float shipY);
void moveBullet(Bullet& shipBullet);
void checkBulletCollision(Bullet& shipBullet, std::vector<Alien>& aliens);
void renderBullet(const Bullet& shipBullet, SDL_Renderer* renderer, SDL_Texture* bulletTexture);

#endif
