#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

#define WINDOW_WIDTH 680
#define WINDOW_HEIGHT 400

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Surface *surface;
SDL_Texture *texture;
SDL_Rect srcImg;
SDL_Rect standImg;
SDL_Rect jumpImg;


int track;

void initialize();
void createWindowRendrer(int width, int height);
void gameplay(void);
void quitAll();

int main(){
    initialize();
    createWindowRendrer(WINDOW_WIDTH, WINDOW_HEIGHT);
    gameplay();
    quitAll();
    return 0;
}

void gameplay(void){
    int speed = 10;
    int distance = 0;

    surface = IMG_Load("gfx/jumper.png");
    if(!surface){
        printf("no surface created");
        quitAll();
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if(!texture){
        printf("no texture created\n");
        quitAll();
    }

    SDL_QueryTexture(texture, NULL, NULL, &srcImg.w, &srcImg.h);
    int closeReq = 0;

    srcImg.h /= 3;
    srcImg.w /= 4.5;
    standImg.h = 64;
    standImg.w = 54;
    standImg.x = 0;
    standImg.y = 0;

    int xpos = (WINDOW_WIDTH - srcImg.w);
    int ypos = (WINDOW_HEIGHT - srcImg.h);
    srcImg.x = xpos;
    srcImg.y = ypos;
    int up = 0, down = 0, left = 0, right = 0;
    while(!closeReq){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
            case SDL_QUIT:
                closeReq = 1;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.scancode){
                case SDL_SCANCODE_UP:
                    up = 1;
                    break;
                case SDL_SCANCODE_DOWN:
                    down = 1;
                    break;
                case SDL_SCANCODE_LEFT:
                    left = 1;
                    break;
                case SDL_SCANCODE_RIGHT:
                    right = 1;
                    break;
                }
                break;
            /* case SDL_KEYUP:
                switch(event.key.keysym.scancode){
                case SDL_SCANCODE_UP:
                    up = 0;
                    break;
                case SDL_SCANCODE_DOWN:
                    down = 0;
                    break;
                case SDL_SCANCODE_LEFT:
                    left = 0;
                    break;
                case SDL_SCANCODE_RIGHT:
                    right = 0;
                    break;
                }
            break; */
            }
        }
        if(up == 1 && down == 0 && distance < 70){
            srcImg.y -= speed;
            distance += 10;
        } else if(up == 1 && distance > 0){
            srcImg.y += speed;
            distance -= 10;
            down = 1;
        } else{
            up = 0;
            down = 0;
        }
        if(left == 1){
            srcImg.x -= speed;
            left = 0;
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, &standImg, &srcImg);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / 70);
    }
    return;
}

void quitAll(){
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
}