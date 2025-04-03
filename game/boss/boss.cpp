#include "D:\Space Invaders\game\boss\boss.h"
#include "D:\Space Invaders\src\include\SDL2\SDL_image.h"
#include <iostream>

#define ALIEN_BULLET_WIDTH 10

void initializeBoss(Boss& boss, SDL_Renderer* renderer) {
    boss.x = 400;
    boss.y = 50;
    boss.health = BOSS_HEALTH;
    boss.active = true;

    SDL_Surface* bossSurface = IMG_Load("assets/boss.png");
    if (bossSurface == nullptr) {
        std::cerr << "Không thể tải ảnh boss! Lỗi SDL_image: " << IMG_GetError() << std::endl;
        exit(1);
    }

    boss.texture = SDL_CreateTextureFromSurface(renderer, bossSurface);
    SDL_FreeSurface(bossSurface);
    if (boss.texture == nullptr) {
        std::cerr << "Không thể tạo texture từ surface boss! Lỗi SDL: " << SDL_GetError() << std::endl;
        exit(1);
    }
}

void renderBoss(const Boss& boss, SDL_Renderer* renderer) {
    if (boss.active) {
        SDL_Rect bossRect = { static_cast<int>(boss.x), static_cast<int>(boss.y), BOSS_WIDTH, BOSS_HEIGHT };
        SDL_RenderCopy(renderer, boss.texture, nullptr, &bossRect);
    }
}

void handleBossHit(Boss& boss) {
    if (boss.active && boss.health > 0) {
        boss.health--;
        if (boss.health % 20 == 0 && boss.health > 0) {
            boss.x += (boss.x > 0 ? 1 : -1) * BOSS_SPEED;
            const_cast<float&>(BOSS_SPEED) *= 2;
        }
        if (boss.health <= 0) {
            boss.active = false;
        }
    }
}

void moveBoss(Boss& boss) {
    static bool movingRight = true;

    if (boss.active) {
        if (movingRight) {
            boss.x += BOSS_SPEED;
            if (boss.x + BOSS_WIDTH >= 1000) {
                movingRight = false;
            }
        } else {
            boss.x -= BOSS_SPEED;
            if (boss.x <= 0) {
                movingRight = true;
            }
        }
    }
}

void bossShoot(Boss& boss, std::vector<Bullet>& bullets) {
    if (boss.active) {
        bullets.push_back({
            boss.x + BOSS_WIDTH / 2 - (2 * ALIEN_BULLET_WIDTH) / 2,
            boss.y + BOSS_HEIGHT,
            true,
            true
        });

        if (boss.health <= 25) {
            bullets.push_back({
                boss.x - (2 * ALIEN_BULLET_WIDTH),
                boss.y + BOSS_HEIGHT,
                true,
                true
            });

            bullets.push_back({
                boss.x + BOSS_WIDTH,
                boss.y + BOSS_HEIGHT,
                true,
                true
            });
        }
    }
}
