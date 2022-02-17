#include <stdio.h>
#include <math.h>
#include<stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

#define WINDOW_WIDTH 680
#define WINDOW_HEIGHT 400
#define MOVE_SPEED 4 //Move speed of all move.
#define JUMP_DISTANCE 140
#define MIN_VELOCITY -60

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Surface *surface;
SDL_Surface *surface2;
SDL_Texture *texture;
SDL_Texture *texture2;
SDL_Rect stairImg[5];
SDL_Rect srcImg;
SDL_Rect standImg;
SDL_Rect jumpImg;
SDL_Rect imgPtr;//image pointer.


int track;

void initialize();
void createWindowRendrer(int width, int height);
void setImgVariables();
int getRandInt();
void getInput(int *, int *, int *, int *);
void gameplay(void);
void closeAll();


int main(){
    initialize();
    createWindowRendrer(WINDOW_WIDTH, WINDOW_HEIGHT);
    gameplay();
    closeAll();
    return 0;
}

void getInput(int *left, int *right, int *up, int *closeReq){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch(event.type){
        case SDL_QUIT:
            *closeReq = 1;
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
    SDL_RenderCopy(renderer, texture2, NULL, &stairImg[0]);
    SDL_RenderCopy(renderer, texture2, NULL, &stairImg[1]);
    SDL_RenderCopy(renderer, texture, &imgPtr, &srcImg);
    SDL_RenderPresent(renderer);
    return;
}

int getRandInt(){
    return rand() % 616;
}

void gameplay(void){

    surface = IMG_Load("gfx/jumper.png");
    surface2 = IMG_Load("gfx/obstacle2.png");
    if(!surface && !surface2){
        printf("no surface created");
        closeAll();
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    texture2 = SDL_CreateTextureFromSurface(renderer, surface2);
    SDL_FreeSurface(surface);
    SDL_FreeSurface(surface2);
    if(!texture && !texture2){
        printf("no texture created\n");
        closeAll();
    }
    SDL_QueryTexture(texture2, NULL, NULL, &stairImg[0].w, &stairImg[0].h);
    SDL_QueryTexture(texture2, NULL, NULL, &stairImg[1].w, &stairImg[1].h);
    SDL_QueryTexture(texture, NULL, NULL, &srcImg.w, &srcImg.h);

    setImgVariables();

    float x_pos = 20;
    float y_pos = (WINDOW_HEIGHT - srcImg.h);

    srcImg.x = x_pos;
    srcImg.y = y_pos;
    stairImg[0].x = getRandInt();
    stairImg[0].y = 45;
    stairImg[1].x = getRandInt();
    stairImg[1].y = 300;
    int up = 0, down = 0, left = 0, right = 0, closeReq = 0;
    float speed = 6, jumpHeight = JUMP_DISTANCE;

    while(!closeReq){
        imgPtr = standImg;
        int x_speed = abs(speed);
        getInput(&left, &right, &up, &closeReq);

        if(up == 1 && y_pos - speed <= WINDOW_HEIGHT - srcImg.h){
            imgPtr = jumpImg;
            if(jumpHeight <= 0 && jumpHeight >= -6){
                speed = -(speed + 3);
            }
            y_pos -= speed;
            jumpHeight -= abs(speed);
        } else{
            up = 0;
            speed = 6;
            jumpHeight = JUMP_DISTANCE;
        }
        if(right == 1){
            if(!up){
                speed = 5;
                right = 0;
            }
            x_pos += x_speed * (x_pos + x_speed < WINDOW_WIDTH - srcImg.w);
        }
        if(left == 1){
            if(!up){
                speed = 6;
                left = 0;
            }
            x_pos -= x_speed * (x_pos - x_speed > srcImg.w - 40);
        }
        srcImg.x = (int)x_pos;
        srcImg.y = (int)y_pos;
        renderFunc();
        SDL_Delay(1000 / 70);
    }
    return;
}

void closeAll(){
    SDL_DestroyTexture(texture);
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
        printf("Not able to create window %d\n", track++);
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    return;
}

void initialize(){
    int gotscreen = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    if(gotscreen != 0){
        printf("Not able to initialize window %d\n", track++);
        return;
    }
    srand((unsigned)time(NULL));
    return;
}