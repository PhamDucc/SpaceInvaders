#include "D:\Space Invaders\core\init\init.h"
#include "D:\Space Invaders\core\window\window.h"
#include "D:\Space Invaders\objects\ship\ship.h"
#include "D:\Space Invaders\objects\alien\alien.h"
#include "D:\Space Invaders\objects\shipbullet\shipbullet.h"
#include "D:\Space Invaders\objects\alienbullet\alienbullet.h"
#include "D:\Space Invaders\core\game\game.h"
#include <chrono>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

#undef main

SDL_Texture* heartTexture = nullptr;

int main(int argc, char* argv[]) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (!initSDL(window, renderer)) {
        return 1;
    }

    runGame(window, renderer);

    return 0;
}