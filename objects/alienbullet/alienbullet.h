#ifndef ALIENBULLET_H
#define ALIENBULLET_H

#include "D:\Space Invaders\src\include\SDL2\SDL.h"
#include <vector>
#include "D:\Space Invaders\objects\shipbullet\shipbullet.h"

const int ALIEN_BULLET_WIDTH = 35;
const int ALIEN_BULLET_HEIGHT = 25;
const float ALIEN_BULLET_SPEED = 0.15f;

void moveAlienBullets(std::vector<Bullet>& alienBullets, int screenHeight);
void renderAlienBullets(const std::vector<Bullet>& alienBullets, SDL_Renderer* renderer, SDL_Texture* alienBulletTexture);

#endif
