#ifndef BOSS_H
#define BOSS_H

#include "D:\Space Invaders\src\include\SDL2\SDL.h"
#include <vector>
#include "D:\Space Invaders\game\shipbullet\shipbullet.h"

const int BOSS_WIDTH = 300;
const int BOSS_HEIGHT = 200;
const int BOSS_HEALTH = 50;
const float BOSS_SPEED = 0.05f;

const int BOSS_BULLET_WIDTH = 50;
const int BOSS_BULLET_HEIGHT = 35;

struct Boss {
    float x, y;
    int health;
    bool active;
    SDL_Texture* texture;
};

void initializeBoss(Boss& boss, SDL_Renderer* renderer);
void renderBoss(const Boss& boss, SDL_Renderer* renderer);
void handleBossHit(Boss& boss);
void moveBoss(Boss& boss);
void bossShoot(Boss& boss, std::vector<Bullet>& bullets);

#endif
