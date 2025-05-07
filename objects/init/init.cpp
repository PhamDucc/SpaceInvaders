#include "D:\Space Invaders\core\init\init.h"

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
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL không thể khởi tạo! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (!IMG_Init(IMG_INIT_PNG)) {
        std::cerr << "SDL_image không thể khởi tạo! IMG_Error: " << IMG_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf không thể khởi tạo! TTF_Error: " << TTF_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Space Shooter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Không thể tạo cửa sổ! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Không thể tạo renderer! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

Mix_Chunk* shipShootSound = nullptr;

void loadSounds() {
    shipShootSound = Mix_LoadWAV("assets/sounds/shipshoot.wav");
    if (shipShootSound == nullptr) {
        std::cerr << "Không thể tải âm thanh shipshoot.wav! Lỗi SDL_mixer: " << Mix_GetError() << std::endl;
        exit(1);
    }
}
