#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_test_images.h>
#include <SDL2/SDL_timer.h>
#include <time.h>

// I will need to uncomment  these if i am using these
// variable in other files.
// but for now only the image vars are used in other 
// file, (gameFuncs.c) .


// extern since defined in the header file.

//extern SDL_Window *window;
//extern SDL_Renderer *renderer;
//extern SDL_Surface *jumperSurface;
// For background .
//extern SDL_Surface *backgndSurface;
//extern SDL_Surface *tileSurface;
//extern SDL_Texture *jumperTexture;
//extern SDL_Texture *tileTexture;
//extern SDL_Texture *backgndTexture;
// And So ON .........


// included for gameFuncs.c file.
extern SDL_Rect tileImg[6];
extern SDL_Rect srcImg;
extern SDL_Rect standImg;
extern SDL_Rect jumpImg;
extern SDL_Rect imgPtr;    //Image pointer(figuratively).
extern SDL_Rect bgImg;


// Sdl functions.
void initialize();
void createWindowRenderer(int width, int height);
void queryTexture();
void createSurfaceAndTexture();
void renderFunc();
void getInput(int *, int *, int *, int *,int *);
void closeAll();


