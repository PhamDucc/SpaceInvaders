#ifndef AUDIO_H
#define AUDIO_H

#include "SDL_mixer.h"
#include <string>

class Audio {
public:
    static bool init();
    static void close();
    static bool loadSound(const char* path);
    static void playShipShootSound();
    static void playAlienHitSound();
    static void playBackgroundMusic();
    static void stopBackgroundMusic();
    static void cleanup();

private:
    static Mix_Chunk* shipShootSound;
    static Mix_Chunk* alienHitSound;
    static Mix_Music* backgroundMusic;
    static bool initialized;
};

#endif