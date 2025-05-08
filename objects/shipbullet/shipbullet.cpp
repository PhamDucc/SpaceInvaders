#include "D:\Space Invaders\objects\ship\ship.h"
#include "D:\Space Invaders\objects\shipbullet\shipbullet.h"
#include "D:\Space Invaders\audio\audio.h"

void createBullet(Bullet& shipBullet, float shipX, float shipY) {
    if (!shipBullet.active) { 
        shipBullet.x = shipX + SHIP_WIDTH / 2 - BULLET_WIDTH / 2;
        shipBullet.y = shipY;
        shipBullet.active = true;
    }
}

void moveBullet(Bullet& shipBullet) {
    if (shipBullet.active) {
        shipBullet.y -= BULLET_SPEED;
        if (shipBullet.y < 0) {
            shipBullet.active = false;
        }
    }
}

void checkBulletCollision(Bullet& shipBullet, std::vector<Alien>& aliens) {
    if (shipBullet.active) {
        for (auto& alien : aliens) {
            if (alien.active &&
                shipBullet.x < alien.x + ALIEN_WIDTH && shipBullet.x + BULLET_WIDTH > alien.x &&
                shipBullet.y < alien.y + ALIEN_HEIGHT && shipBullet.y + BULLET_HEIGHT > alien.y) {
                shipBullet.active = false;
                alien.health--;
                if (alien.health <= 0) {
                    alien.active = false; 
                }
                Audio::playAlienHitSound(); // Add sound effect when alien is hit
                break;
            }
        }
    }
}

void renderBullet(const Bullet& shipBullet, SDL_Renderer* renderer, SDL_Texture* bulletTexture) {
    if (shipBullet.active) {
        SDL_Rect bulletRect = { static_cast<int>(shipBullet.x), static_cast<int>(shipBullet.y), BULLET_WIDTH, BULLET_HEIGHT };
        SDL_RenderCopy(renderer, bulletTexture, nullptr, &bulletRect);
    }
}
