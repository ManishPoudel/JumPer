#include <stdio.h>
#include <math.h>
#include<stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

#define WINDOW_WIDTH 680
#define WINDOW_HEIGHT 400
#define JUMP_DISTANCE 140

struct Jumper{
    int x_pos;
    int y_pos;
    int speed;
    int jumpHeight;
    int up, left, right;
};


SDL_Window *window;
SDL_Renderer *renderer;
SDL_Surface *surface;
SDL_Surface *surface2;
SDL_Texture *texture;
SDL_Texture *texture2;
SDL_Rect tileImg[5];
SDL_Rect srcImg;
SDL_Rect standImg;
SDL_Rect jumpImg;
SDL_Rect imgPtr;//image pointer.

int track = 0; //for error detection.
int closeReq = 0;
void initialize();
void createWindowRendrer(int width, int height);
void setImgVariables();
int getRandInt();
void getInput(int *, int *, int *);
void freeSurface();
void setTilesPos();
void queryTexture();
void createSurfaceAndTexture();
void renderFunc();
void controlMovement(struct Jumper *);
void gameplay(void);
void closeAll();


int main(){
    initialize();
    createWindowRendrer(WINDOW_WIDTH, WINDOW_HEIGHT);
    gameplay();
    closeAll();
    return 0;
}

//Main game play loop is this.
void gameplay(void){
    createSurfaceAndTexture();
    queryTexture();
    setImgVariables();
    setTilesPos();

    int x_pos = tileImg[0].x + 10;
    int y_pos = tileImg[0].y - srcImg.h;
    srcImg.x = x_pos;
    srcImg.y = y_pos;
    struct Jumper jumper = { x_pos,y_pos,6,JUMP_DISTANCE,0,0,0 };
    while(!closeReq){
        imgPtr = standImg;
        controlMovement(&jumper);
        renderFunc();
        SDL_Delay(1000 / 70);
    }
    return;
}

void controlMovement(struct Jumper *jumper){
    int  x_speed = abs(jumper->speed);
    getInput(&jumper->left, &jumper->right, &jumper->up);

    if(jumper->up == 1 && jumper->y_pos - jumper->speed <= WINDOW_HEIGHT - srcImg.h){
        imgPtr = jumpImg;
        if(jumper->jumpHeight <= 0 && jumper->jumpHeight >= -6){
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
        if(!jumper->up){
            jumper->speed = 5;
        }
        jumper->x_pos += x_speed * (jumper->x_pos + x_speed < WINDOW_WIDTH - srcImg.w);
    }
    if(jumper->left == 1){
        if(!jumper->up){
            jumper->speed = 6;
        }
        jumper->x_pos -= x_speed * (jumper->x_pos - x_speed > srcImg.w - 38);
    }
    srcImg.x = jumper->x_pos;
    srcImg.y = jumper->y_pos;
    return;
}

void getInput(int *left, int *right, int *up){
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
            // To detect the leaving of left right keys (Must do).
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

void renderFunc(){
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture2, NULL, &tileImg[0]);
    SDL_RenderCopy(renderer, texture2, NULL, &tileImg[1]);
    SDL_RenderCopy(renderer, texture, &imgPtr, &srcImg);
    SDL_RenderPresent(renderer);
    return;
}

int getRandInt(){   //Returns random for y position of tile.
    return rand() % 616;
}

void freeSurface(){
    SDL_FreeSurface(surface);
    SDL_FreeSurface(surface2);
    return;
}

void createSurfaceAndTexture(){
    surface = IMG_Load("gfx/jumper.png");
    surface2 = IMG_Load("gfx/obstacle2.png");
    if(!surface && !surface2){
        printf("Not able to create surface: %d", track++);
        closeAll();
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    texture2 = SDL_CreateTextureFromSurface(renderer, surface2);
    freeSurface();
    if(!texture && !texture2){
        printf("Not able to create texture: %d\n", track++);
        closeAll();
    }
    return;
}

void queryTexture(){
    SDL_QueryTexture(texture2, NULL, NULL, &tileImg[0].w, &tileImg[0].h);
    SDL_QueryTexture(texture2, NULL, NULL, &tileImg[1].w, &tileImg[1].h);
    SDL_QueryTexture(texture, NULL, NULL, &srcImg.w, &srcImg.h);
    return;
}

void setTilesPos(){
    tileImg[0].x = getRandInt();
    tileImg[0].y = 300;
    tileImg[1].x = getRandInt();
    tileImg[1].y = 45;
    return;
}



void closeAll(){
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(texture2);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return;
}

void createWindowRendrer(int width, int height){
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
    srand((unsigned)time(NULL));
    return;
}