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
    SDL_Rect srcImg;
    SDL_QueryTexture(texture, NULL, NULL, &srcImg.w, &srcImg.h);
    int closeReq = 0;

    while(!closeReq){

       /*  SDL_Event event;

        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                closeReq = 1;
            }
        }
 */
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, &srcImg);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000);
        closeReq = 1;
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