#include "D:\Space Invaders\game\alienbullet\alienbullet.h"

const int ALIEN_BULLET_WIDTH = 35;
const int ALIEN_BULLET_HEIGHT = 25;
const float ALIEN_BULLET_SPEED = 0.15f;

void moveAlienBullets(std::vector<Bullet>& alienBullets, int screenHeight) {
    for (auto& bullet : alienBullets) {
        if (bullet.active) {
            bullet.y += ALIEN_BULLET_SPEED;
            if (bullet.y > screenHeight) {
                bullet.active = false;
            }
        }
    }
}

void renderAlienBullets(const std::vector<Bullet>& alienBullets, SDL_Renderer* renderer, SDL_Texture* alienBulletTexture) {
    for (const auto& bullet : alienBullets) {
        if (bullet.active) {
            SDL_Rect bulletRect = {
                static_cast<int>(bullet.x),
                static_cast<int>(bullet.y),
                ALIEN_BULLET_WIDTH,
                ALIEN_BULLET_HEIGHT
            };
            SDL_RenderCopy(renderer, alienBulletTexture, nullptr, &bulletRect);
        }
    }
}
