#ifndef WINDOW_H
#define WINDOW_H

#include "D:\Space Invaders\src\include\SDL2\SDL.h"
#include "D:\Space Invaders\src\include\SDL2\SDL_image.h"
#include "D:\Space Invaders\src\include\SDL2\SDL_ttf.h"
#include <iostream>

SDL_Window* initializeWindow();
SDL_Renderer* initializeRenderer(SDL_Window* window);

#endif
