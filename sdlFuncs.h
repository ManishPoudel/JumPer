#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_test_images.h>
#include <SDL2/SDL_timer.h>


// Sdl functions.
void initialize();
void createWindowRenderer(int width, int height);
void createSurfaceAndTexture();
void renderFunc();
void getInput(int *, int *, int *, int *,int *);
void closeAll();


