#ifndef INIT_H
#define INIT_H

#include "D:\Space Invaders\src\include\SDL2\SDL.h"
#include "D:\Space Invaders\src\include\SDL2\SDL_image.h"
#include "D:\Space Invaders\src\include\SDL2\SDL_ttf.h"
#include "D:\Space Invaders\src\include\SDL2\SDL_mixer.h"
#include <iostream>

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

SDL_Window* initializeWindow();
SDL_Renderer* initializeRenderer(SDL_Window* window);
SDL_Texture* loadTexture(const char* filePath, SDL_Renderer* renderer);
bool initSDL(SDL_Window*& window, SDL_Renderer*& renderer);


#endif
