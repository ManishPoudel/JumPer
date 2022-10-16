#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "sdl_vars.h"
#include "game_vars.h"
#include "functions.h"

int track = 0;  //For error detection.
int closeReq = 0;
int out = 0;    //If player is out 1.

int main(){
    initialize();
    createWindowRenderer(WINDOW_WIDTH, WINDOW_HEIGHT);
    gamePlay();
    closeAll();
    return 0;
}

//Main game play loop is this.
void gamePlay(void){
    createSurfaceAndTexture();
    queryTexture();
    setImgVariables();
    setTilesPos();

    int x_pos = tileImg[1].x + 10;
    int y_pos = tileImg[1].y - srcImg.h;
    srcImg.x = x_pos;
    srcImg.y = y_pos;

    //Our Character.
    struct Jumper jumper = { x_pos,y_pos,6,JUMP_DISTANCE,0,0,0,0 };
    while(!closeReq){
        imgPtr = standImg;
        out = jumper.y_pos >= WINDOW_HEIGHT - srcImg.h;
        closeReq = out; //Remove when exit screen is ready.
        moveTiles();
        attachJumperToTiles(&jumper);
        controlMovement(&jumper);
        renderFunc();
        SDL_Delay(1000 / 60);
    }
    return;
}

int isTilesPos(struct Jumper *jumper){
    for(int i = 0;i < 6;i++){
        if(jumper->x_pos + JUMPER_WIDTH >= tileImg[i].x + 2 &&
            jumper->x_pos <= (tileImg[i].x + 58) &&
            (jumper->y_pos + JUMPER_HEIGHT) >= (tileImg[i].y - 8) &&
            (jumper->y_pos + JUMPER_HEIGHT) <= tileImg[i].y){
            return 1;
        }
    }
    return 0;
}

int attachJumperToTiles(struct Jumper *jumper){
    if(isTilesPos(jumper)){
        jumper->y_pos += 1;
        jumper->down = 1;
    }
    return 1;
}

void moveTiles(){
    for(int i = 0;i < 6;i++){
        tileImg[i].y = (tileImg[i].y + 1) % 400;
        if(tileImg[i].y > WINDOW_HEIGHT + 16){
            tileImg[i].x = getRandInt();
        }
    }
    return;
}


void controlMovement(struct Jumper *jumper){
    int  x_speed = abs(jumper->speed);
    getInput(&jumper->left, &jumper->right, &jumper->up, &jumper->down);

    if((jumper->up == 1) && !jumper->down /* && !isTilesPos(jumper) */){
        imgPtr = jumpImg;
        if(jumper->jumpHeight <= 0 && jumper->jumpHeight >= -8){
            jumper->speed = -(jumper->speed + 3);
        }
        jumper->y_pos -= jumper->speed;
        jumper->jumpHeight -= x_speed;
    } else{
        jumper->up = 0;
        jumper->speed = 6;
        jumper->jumpHeight = JUMP_DISTANCE;
    }
    if(jumper->right == 1){
        /* if(!jumper->up){ //If you want unique x speed.
            jumper->speed = 5;
        } */
        jumper->x_pos += x_speed *
            (jumper->x_pos + x_speed < WINDOW_WIDTH - srcImg.w) - 1;
    }
    if(jumper->left == 1){
        /* if(!jumper->up){
            jumper->speed = 6;
        } */
        jumper->x_pos -= x_speed *
            (jumper->x_pos - x_speed > srcImg.w - 38) - 1;
    }
    srcImg.x = jumper->x_pos;
    srcImg.y = jumper->y_pos;
    return;
}

void getInput(int *left, int *right, int *up, int *down){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch(event.type){
        case SDL_QUIT:
            closeReq = 1;
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

int getRandInt(){   //Returns random for X position of tile.
    return rand() % 616;
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

void setImgVariables(){
    srcImg.h /= 2;
    srcImg.w /= 4;
    standImg.h = 64;
    standImg.w = 54;
    standImg.x = 0;
    standImg.y = 0;
    jumpImg.h = 64;
    jumpImg.w = 54;
    jumpImg.x = 64;
    jumpImg.y = 0;
    return;
}

void setTilesPos(){
    for(int i = 0;i < 5;i++){
        tileImg[i].x = getRandInt();
        tileImg[i].y = (i + 1) * 70;
    }
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

//  THATS ALL.  THANK YOU!! :-D