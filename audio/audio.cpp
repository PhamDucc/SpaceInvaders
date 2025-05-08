#include "audio.h"
#include <iostream>

Mix_Chunk* Audio::shipShootSound = nullptr;
Mix_Chunk* Audio::alienHitSound = nullptr;
bool Audio::initialized = false;

bool Audio::init() {
    if (initialized) {
        return true;
    }

    // Initialize SDL_mixer with specific flags for WAV support
    int flags = MIX_INIT_MP3 | MIX_INIT_OGG;  // Add basic audio format support
    int initted = Mix_Init(flags);

    if ((initted & flags) != flags) {
        std::cerr << "Mix_Init failed to initialize required loaders! Mix_Error: " << Mix_GetError() << std::endl;
        // Continue anyway as WAV might still work
    }

    // Open audio device
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer initialization failed! Mix_Error: " << Mix_GetError() << std::endl;
        return false;
    }
    
    std::cout << "SDL_mixer initialized successfully" << std::endl;

    // Try to load sound with error details
    shipShootSound = Mix_LoadWAV("assets/sounds/shipshoot.wav");
    if (!shipShootSound) {
        std::cerr << "Failed to load shipshoot.wav! Mix_Error: " << Mix_GetError() << std::endl;
        // Print additional debug info
        std::cerr << "Attempted to load from path: assets/sounds/shipshoot.wav" << std::endl;
        Mix_CloseAudio();
        return false;
    }
    
    std::cout << "Loaded shipshoot.wav successfully" << std::endl;

    alienHitSound = Mix_LoadWAV("assets/sounds/Alien zapped.wav");
    if (!alienHitSound) {
        std::cerr << "Failed to load Alien zapped.wav! Mix_Error: " << Mix_GetError() << std::endl;
        Mix_FreeChunk(shipShootSound);
        Mix_CloseAudio();
        return false;
    }

    std::cout << "Loaded Alien zapped.wav successfully" << std::endl;

    initialized = true;
    return true;
}

void Audio::close() {
    cleanup();
    Mix_CloseAudio();
    initialized = false;
}

bool Audio::loadSound(const char* path) {
    Mix_Chunk* sound = Mix_LoadWAV(path);
    if (!sound) {
        std::cerr << "Không thể tải âm thanh " << path << "! Mix_Error: " << Mix_GetError() << std::endl;
        return false;
    }
    return true;
}

void Audio::playShipShootSound() {
    if (!initialized) {
        std::cerr << "Attempted to play sound but audio is not initialized" << std::endl;
        return;
    }
    if (!shipShootSound) {
        std::cerr << "Attempted to play sound but shipShootSound is null" << std::endl;
        return;
    }
    
    int channel = Mix_PlayChannel(-1, shipShootSound, 0);
    if (channel == -1) {
        std::cerr << "Failed to play sound! Mix_Error: " << Mix_GetError() << std::endl;
    } else {
        std::cout << "Playing ship shoot sound on channel " << channel << std::endl;
    }
}

void Audio::playAlienHitSound() {
    if (initialized && alienHitSound) {
        Mix_PlayChannel(-1, alienHitSound, 0);
    }
}

void Audio::cleanup() {
    if (shipShootSound) {
        Mix_FreeChunk(shipShootSound);
        shipShootSound = nullptr;
    }
    if (alienHitSound) {
        Mix_FreeChunk(alienHitSound);
        alienHitSound = nullptr;
    }
}