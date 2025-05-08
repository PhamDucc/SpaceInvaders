#ifndef GAME_H
#define GAME_H

#include "D:\Space Invaders\core\init\init.h"
#include "D:\Space Invaders\core\window\window.h"
#include "D:\Space Invaders\objects\ship\ship.h"
#include "D:\Space Invaders\objects\alien\alien.h"
#include "D:\Space Invaders\objects\shipbullet\shipbullet.h"
#include "D:\Space Invaders\objects\alienbullet\alienbullet.h"
#include "D:\Space Invaders\menu\menu.h"
#include "D:\Space Invaders\audio\audio.h"
#include <vector>
#include <chrono>

void runGame(SDL_Window* window, SDL_Renderer* renderer);

#endif
