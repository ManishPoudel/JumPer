#ifndef initialize_sdl
#define initialize_sdl
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_pixels.h>
// for delay
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
extern SDL_Rect bgImgPtr;   //Image pointer(figuratively).
extern SDL_Rect destTextRect[6];


// Sdl functions.
void initializeSdl();
void createWindowRenderer(int width, int height);
void queryTexture();
void createSurfaceAndTexture();
void renderFunc();
void renderCopyGamePlay();


void drawMenuRect();
void drawMenuTexts();
void drawSelectBoxMenu(int *enterArrow, int *upArrow, int *downArrow
                       , int *menuOptPointer);
void printScoreBoard(char *score);

void renderAudio(int audio);

void getInput(int *, int *, int *, int *, int *);
void closeAll();

#endif
