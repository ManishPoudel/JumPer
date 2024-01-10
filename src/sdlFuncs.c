#include "../includes/sdlFuncs.h"
#include "../includes/gameVars.h"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_ttf.h>


// I might need to put these in structure.
// Declared in header for global access
// but must be defined in .c file too
SDL_Window *window;
SDL_Renderer *renderer;
// surface for jumper, background and tiles.
SDL_Surface *jumperSurface;
SDL_Surface *backgndSurface;
SDL_Surface *tileSurface;
SDL_Surface *menuTextSurface;
// texture for jumper, background and tiles.
SDL_Texture *jumperTexture;
SDL_Texture *backgndTexture;
SDL_Texture *tileTexture;
SDL_Texture *menuTextTexture;

SDL_Color color3={0,0,0,255};
// for the jumping tiles, 
// only 6 at a time is generated.
SDL_Rect tileImg[6];
SDL_Rect srcImg;
SDL_Rect standImg;
SDL_Rect jumpImg;
SDL_Rect imgPtr;    //Image pointer(figuratively).
SDL_Rect bgImg;
SDL_Rect bgImgPtr;   //Image pointer(figuratively).
// Destination text reactangle.
SDL_Rect destTextRect;

TTF_Font *font;

void getInput(int *left, int *right, int *up, int *down,int *quitGame){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch(event.type){
        case SDL_QUIT:
            *quitGame = 1;
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.scancode){
            case SDL_SCANCODE_UP:
                *up = 1;
                *down = 0;
                break;
            case SDL_SCANCODE_LEFT:
                *left = 1;
                break;
            case SDL_SCANCODE_RIGHT:
                *right = 1;
                break;
            default:
                break;
            }
            break;
        case SDL_KEYUP:
            // To detect the leaving of left right keys (must do).
            switch(event.key.keysym.scancode){
            case SDL_SCANCODE_LEFT:
                *left = 0;
                break;
            case SDL_SCANCODE_RIGHT:
                *right = 0;
                break;
            default:
                    break;
            }
            break;
        }
    }
    return;
}
void renderCopy(){
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer,backgndTexture,NULL,&bgImg);
    SDL_RenderCopy(renderer,backgndTexture,NULL,&bgImgPtr);
    for(int i = 0;i < 6;i++){
        SDL_RenderCopy(renderer, tileTexture, NULL, &tileImg[i]);
    }
    SDL_RenderCopy(renderer, jumperTexture, &imgPtr, &srcImg);
    return;
}
// Renders in screen what is copied to renderer.
void renderFunc(){
    SDL_RenderPresent(renderer);
    return;
}

void drawMenuRect(){
    SDL_Rect menuOutline={100,100,100,100};
    SDL_Rect menuOutline2={99,99,102,102};
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderDrawRect(renderer, &menuOutline);
    SDL_RenderDrawRect(renderer, &menuOutline2);
//    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderCopy(renderer, menuTextTexture, NULL,&destTextRect);
        return;
}

void freeSurface(){
    SDL_FreeSurface(jumperSurface);
    SDL_FreeSurface(tileSurface);
    SDL_FreeSurface(backgndSurface);
    SDL_FreeSurface(menuTextSurface);
    return;
}

void createSurfaceAndTexture(){
    backgndSurface= IMG_Load("gfx/background2.png");
    jumperSurface= IMG_Load("gfx/jumper.png");
    tileSurface = IMG_Load("gfx/obstacle.png");
    // for text rendering.
    menuTextSurface=TTF_RenderText_Solid(font,"hello", color3);

    if(!jumperSurface&& !tileSurface && !backgndSurface &&
        !menuTextSurface){
        printf("Not able to create surface: track 1\n");
        closeAll();
    }
    jumperTexture= SDL_CreateTextureFromSurface(renderer, jumperSurface);
    tileTexture = SDL_CreateTextureFromSurface(renderer, tileSurface);
    backgndTexture= SDL_CreateTextureFromSurface(renderer, backgndSurface);
    menuTextTexture=SDL_CreateTextureFromSurface(renderer, menuTextSurface);
    freeSurface();
    if(!jumperTexture && !tileTexture && !backgndTexture && 
        !menuTextTexture){
        printf("Not able to create texture: track 2\n");
        closeAll();
    }
    return;
}

//Query texture for their dimensions and store value in sdlrect.
void queryTexture(){
    for(int i = 0;i < 6;i++){
        SDL_QueryTexture(tileTexture, NULL, NULL, &tileImg[i].w, &tileImg[i].h);
    }
    SDL_QueryTexture(jumperTexture, NULL, NULL, &srcImg.w, &srcImg.h);
    SDL_QueryTexture(backgndTexture, NULL, NULL, &bgImg.w, &bgImg.h);
    SDL_QueryTexture(menuTextTexture, NULL, NULL, &destTextRect.w, &destTextRect.h);
    return;
}


void closeAll(){
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyTexture(jumperTexture);
    SDL_DestroyTexture(tileTexture);
    SDL_DestroyTexture(backgndTexture);
    SDL_DestroyTexture(menuTextTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return;
}

void createWindowRenderer(int width, int height){
    window = SDL_CreateWindow("JuMpeR", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width, height, SDL_WINDOW_SHOWN);

    if(window == NULL){
        printf("Not able to create window:track 3\n");
        return;
    }
    renderer = SDL_CreateRenderer(window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(renderer == NULL){
        printf("Not able to create Renderer:track 4");
    }
    return;
}

void initializeSdl(){
    int gotscreen = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    if(gotscreen != 0){
        printf("Not able to initialize window: track 5\n");
        return;
    }
    // Initialize SDL_ttf.
    TTF_Init();
    font=TTF_OpenFont("gfx/DejaVuSans.ttf", 40);
    if(!font){
        printf("unable font");
    }
    return;
}
