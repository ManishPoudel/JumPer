#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_test_images.h>
#include <SDL2/SDL_timer.h>
#include <time.h>

// I might need to put these in structure.
// extern since defined in the header file.
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Surface *surface;
extern SDL_Surface *tileSurface;
extern SDL_Texture *texture;
extern SDL_Texture *tileTexture;
extern SDL_Rect tileImg[6];
extern SDL_Rect srcImg;
extern SDL_Rect standImg;
extern SDL_Rect jumpImg;
extern SDL_Rect imgPtr;    //Image pointer(figuratively).


// Sdl functions.
void initialize();
void createWindowRenderer(int width, int height);
void createSurfaceAndTexture();
void renderFunc();
void getInput(int *, int *, int *, int *,int *);
void closeAll();


