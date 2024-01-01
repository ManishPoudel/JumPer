#include "sdlFuncs.h"

// I might need to put these in structure.
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Surface *surface;
SDL_Surface *tileSurface;
SDL_Texture *texture;
SDL_Texture *tileTexture;
SDL_Rect tileImg[6];
SDL_Rect srcImg;
SDL_Rect standImg;
SDL_Rect jumpImg;
SDL_Rect imgPtr;    //Image pointer(figuratively).

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

void renderFunc(){
    SDL_RenderClear(renderer);
    for(int i = 0;i < 6;i++){
        SDL_RenderCopy(renderer, tileTexture, NULL, &tileImg[i]);
    }
    SDL_RenderCopy(renderer, texture, &imgPtr, &srcImg);
    SDL_RenderPresent(renderer);
    return;
}


void freeSurface(){
    SDL_FreeSurface(surface);
    SDL_FreeSurface(tileSurface);
    return;
}

void createSurfaceAndTexture(){
    surface = IMG_Load("gfx/jumper.png");
    tileSurface = IMG_Load("gfx/obstacle2.png");
    if(!surface && !tileSurface){
        printf("Not able to create surface: %d", track++);
        closeAll();
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    tileTexture = SDL_CreateTextureFromSurface(renderer, tileSurface);
    freeSurface();
    if(!texture && !tileTexture){
        printf("Not able to create texture: %d\n", track++);
        closeAll();
    }
    return;
}

void queryTexture(){
    for(int i = 0;i < 6;i++){
        SDL_QueryTexture(tileTexture, NULL, NULL, &tileImg[i].w, &tileImg[i].h);
    }
    SDL_QueryTexture(texture, NULL, NULL, &srcImg.w, &srcImg.h);
    return;
}


void closeAll(){
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(tileTexture);
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
        printf("Not able to create window: %d\n", track++);
        return;
    }
    renderer = SDL_CreateRenderer(window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(renderer == NULL){
        printf("Not able to create Renderer: %d\n", track++);
    }
    return;
}

void initialize(){
    int gotscreen = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    if(gotscreen != 0){
        printf("Not able to initialize window: %d\n", track++);
        return;
    }
    // if(TTF_Init() == -1){
    //     printf("Not able to initialize ttf:%d\n", track++);
    //     printf("TTF_Init: %s\n", TTF_GetError());
    //     exit(2);
    // }
    srand((unsigned)time(NULL));
    return;
}
