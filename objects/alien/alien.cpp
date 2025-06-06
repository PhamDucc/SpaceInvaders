#include "D:\Space Invaders\objects\alien\alien.h"
#include <iostream>

void initializeAliens(std::vector<Alien>& aliens, float startX, float startY) {
    aliens.clear();
    for (int j = 0; j < 10; ++j) {
        aliens.push_back({startX + j * (ALIEN_WIDTH + ALIEN_SPACING), startY, true, 2});
    }
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 10; ++j) {
            aliens.push_back({startX + j * (ALIEN_WIDTH + ALIEN_SPACING), startY + (i + 1) * (ALIEN_HEIGHT + ALIEN_SPACING), true, 1});
        }
    }
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 10; ++j) {
            aliens.push_back({startX + j * (ALIEN_WIDTH + ALIEN_SPACING), startY + (i + 3) * (ALIEN_HEIGHT + ALIEN_SPACING), true, 1});
        }
    }
}

void renderAliens(const std::vector<Alien>& aliens, SDL_Renderer* renderer, SDL_Texture* firstAlienTexture, SDL_Texture* secondAlienTexture, SDL_Texture* thirdAlienTexture) {
    for (const auto& alien : aliens) {
        if (alien.active) {
            SDL_Rect alienRect = { static_cast<int>(alien.x), static_cast<int>(alien.y), ALIEN_WIDTH, ALIEN_HEIGHT };
            if (&alien - &aliens[0] < 10) {
                SDL_RenderCopy(renderer, thirdAlienTexture, nullptr, &alienRect);
            } else if (&alien - &aliens[0] < 30) {
                SDL_RenderCopy(renderer, secondAlienTexture, nullptr, &alienRect);
            } else {
                SDL_RenderCopy(renderer, firstAlienTexture, nullptr, &alienRect);
            }
        }
    }
}

void updateAlienPositions(std::vector<Alien>& aliens, float alienX, float alienY) {
    for (int i = 0; i < 1; ++i) {
        for (int j = 0; j < 10; ++j) {
            aliens[i * 10 + j].x = alienX + j * (ALIEN_WIDTH + ALIEN_SPACING);
            aliens[i * 10 + j].y = alienY + i * (ALIEN_HEIGHT + ALIEN_SPACING);
        }
    }
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 10; ++j) {
            aliens[10 + i * 10 + j].x = alienX + j * (ALIEN_WIDTH + ALIEN_SPACING);
            aliens[10 + i * 10 + j].y = alienY + (i + 1) * (ALIEN_HEIGHT + ALIEN_SPACING);
        }
    }
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 10; ++j) {
            aliens[30 + i * 10 + j].x = alienX + j * (ALIEN_WIDTH + ALIEN_SPACING);
            aliens[30 + i * 10 + j].y = alienY + (i + 3) * (ALIEN_HEIGHT + ALIEN_SPACING);
        }
    }
}