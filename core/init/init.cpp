#include "D:\Space Invaders\core\init\init.h"
#include "D:\Space Invaders\audio\audio.h"
#include <iostream>

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 700;

SDL_Texture* loadTexture(const char* filePath, SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load(filePath);
    if (surface == nullptr) {
        std::cerr << "Unable to load image! IMG_Error: " << IMG_GetError() << std::endl;
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (texture == nullptr) {
        std::cerr << "Unable to create texture! SDL_Error: " << SDL_GetError() << std::endl;
    }

    return texture;
}

bool initSDL(SDL_Window*& window, SDL_Renderer*& renderer) {
    // Initialize SDL with audio support
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Initialize SDL_mixer through Audio class
    if (!Audio::init()) {
        return false;
    }

    // Initialize SDL_image
    if (!IMG_Init(IMG_INIT_PNG)) {
        std::cerr << "SDL_image could not initialize! IMG_Error: " << IMG_GetError() << std::endl;
        return false;
    }

    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
        return false;
    }

    // Create window and renderer using window.h functions
    window = initializeWindow();
    if (!window) {
        return false;
    }

    renderer = initializeRenderer(window);
    if (!renderer) {
        SDL_DestroyWindow(window);
        return false;
    }

    return true;
}

