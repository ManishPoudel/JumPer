#include "../includes/sdlFuncs.h"
#include "../includes/gameVars.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

// I might need to put these in structure.
// Declared in header for global access
// but must be defined in .c file too
SDL_Window *window;
SDL_Renderer *renderer;
// surface for jumper, background and tiles.
SDL_Surface *jumperSurface;
SDL_Surface *backgndSurface;
SDL_Surface *tileSurface;
SDL_Surface *menuTextSurface[6];
// texture for jumper, background and tiles.
SDL_Texture *jumperTexture;
SDL_Texture *backgndTexture;
SDL_Texture *tileTexture;
SDL_Texture *menuTextTexture[6];

SDL_Color color3 = { 0,0,0,255};
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
SDL_Rect destTextRect[6];
//SDL_Rect selectBox = { 230,240,180,40 };
//SDL_Rect *currentBox = &selectBox;
SDL_Rect selectBox[3]={
                        { 230,240,180,40 },
                        { 229,239,182,42 },
                        { 228,238,184,44 }};

TTF_Font *font;
TTF_Font *fontScoreBoard;
TTF_Font *titleFont;

// for audio.
Mix_Chunk *wave=NULL;
Mix_Chunk *waveGameEnd=NULL;

void getInput(int *left, int *right, int *up, int *down, int *quitGame){
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
               // This is for the jumper down movement algorith. 
                *down = 0;
                break;
            case SDL_SCANCODE_LEFT:
                *left = 1;
                break;
            case SDL_SCANCODE_RIGHT:
                *right = 1;
                break;
            case SDL_SCANCODE_DOWN:
               // This is for the jumper down movement algorith. 
                *down = 1;
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

void renderCopyGamePlay(){
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, backgndTexture, NULL, &bgImg);
    SDL_RenderCopy(renderer, backgndTexture, NULL, &bgImgPtr);
    for(int i = 0;i < 6;i++){
        SDL_RenderCopy(renderer, tileTexture, NULL, &tileImg[i]);
    }
    // for rendering score while in game.
    SDL_RenderCopy(renderer, menuTextTexture[5], NULL, &destTextRect[5]);
    SDL_RenderCopy(renderer, jumperTexture, &imgPtr, &srcImg);
    return;
}
// Renders in screen what is copied to renderer.
void renderFunc(){
    SDL_RenderPresent(renderer);
    return;
}

void drawMenuRect(){
    //SDL_RenderClear(renderer);
    //SDL_RenderCopy(renderer, backgndTexture, NULL, &bgImg);
    //Menu outline coordinates and dimensions.
    SDL_Rect menuOutline[6] = {
        {140,90,380,250},
        {141,91,378,248},
        {142,92,376,246},
        {145,95,370,240},
        {146,96,368,238},
        {144,94,372,242},
    };
    //outline coordinates,dimensions and color
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for(int i = 0;i < 5;i++){
        SDL_RenderDrawRect(renderer, &menuOutline[i]);
    }
    //Green outline coordinates,dimensions and color
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderDrawRect(renderer, &menuOutline[5]);
    return;
}

void drawMenuTexts(){
//    SDL_RenderCopy(renderer, menuTextTexture[0], NULL,&destTextRect[0]);
    // "use < arrow to .." text size.
    destTextRect[2].w = 250;
    destTextRect[2].h = 32;
    SDL_RenderCopy(renderer, menuTextTexture[0], NULL, &destTextRect[0]);
    SDL_RenderCopy(renderer, menuTextTexture[1], NULL, &destTextRect[1]);
    SDL_RenderCopy(renderer, menuTextTexture[2], NULL, &destTextRect[2]);
    SDL_RenderCopy(renderer, menuTextTexture[3], NULL, &destTextRect[3]);
    return;
}

void drawSelectBoxMenu(int *enterArrow, int *upArrow, int *downArrow, 
                       int *menuOptPointer){
    if(*upArrow==1 && selectBox[0].y >= 250){
        for(int i=0;i<3;i++)
            selectBox[i].y -= 45;
        *upArrow=0;
    } else if(*downArrow==1 && (selectBox[0].y <= 260)){
        for(int i=0;i<3;i++)
            selectBox[i].y += 45;
        *downArrow=0;
    }
    else if(*enterArrow==1){
        *menuOptPointer=(selectBox[0].y==240)?1:2;
        enterArrow=0;
    }
    for(int i=0;i<3;i++)
        SDL_RenderDrawRect(renderer, &selectBox[i]);
    return;
}

void freeSurface(){
    SDL_FreeSurface(jumperSurface);
    SDL_FreeSurface(tileSurface);
    SDL_FreeSurface(backgndSurface);
    for(int i = 0;i < 6;i++){
        SDL_FreeSurface(menuTextSurface[i]);
    }
    return;
}

void createSurfaceAndTexture(){
    backgndSurface = IMG_Load("gfx/background2.png");
    jumperSurface = IMG_Load("gfx/jumper.png");
    tileSurface = IMG_Load("gfx/obstacle.png");

    // for text rendering.
    menuTextSurface[0] = TTF_RenderText_Solid(titleFont, "JumPer", color3);
    menuTextSurface[1] = TTF_RenderText_Solid(font, "Start Game", color3);
    menuTextSurface[2] = TTF_RenderText_Solid(font, "Use < Arrow to select.", color3);
    menuTextSurface[3] = TTF_RenderText_Solid(font, "Exit", color3);
    // Game title in menu 
    menuTextSurface[4] = IMG_Load("gfx/obstacle.png");
    // make this a number render text.
    menuTextSurface[5] = TTF_RenderText_Solid(fontScoreBoard, "Score:", color3);

    if(!jumperSurface && !tileSurface && !backgndSurface &&
        !menuTextSurface[3]){
        printf("Not able to create surface: track 1\n");
        closeAll();
    }
    jumperTexture = SDL_CreateTextureFromSurface(renderer, jumperSurface);
    tileTexture = SDL_CreateTextureFromSurface(renderer, tileSurface);
    backgndTexture = SDL_CreateTextureFromSurface(renderer, backgndSurface);
    for(int i = 0;i < 6;i++){
        menuTextTexture[i] = SDL_CreateTextureFromSurface(renderer, menuTextSurface[i]);
    }

    freeSurface();

    if(!jumperTexture && !tileTexture && !backgndTexture &&
        !menuTextTexture[3]){
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
    for(int i = 0;i < 6;i++){
        SDL_QueryTexture(menuTextTexture[i], NULL, NULL,
            &destTextRect[i].w, &destTextRect[i].h);
    }
    return;
}

void closeAll(){
    TTF_CloseFont(font);
    TTF_Quit();
    Mix_FreeChunk(wave);
    Mix_FreeChunk(waveGameEnd);
    Mix_CloseAudio();
    Mix_Quit();
    SDL_DestroyTexture(jumperTexture);
    SDL_DestroyTexture(tileTexture);
    SDL_DestroyTexture(backgndTexture);
    for(int i = 0;i < 6;i++){
        SDL_DestroyTexture(menuTextTexture[i]);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return;
}

void printScoreBoard(char *score){
    menuTextSurface[5] = TTF_RenderText_Solid(fontScoreBoard, score, color3);
    menuTextTexture[5] = SDL_CreateTextureFromSurface(renderer, menuTextSurface[5]);
    SDL_FreeSurface(menuTextSurface[5]);
    SDL_QueryTexture(menuTextTexture[5], NULL, NULL,
        &destTextRect[5].w, &destTextRect[5].h);
    return;
}

void sdlOpenFont(){
    font = TTF_OpenFont("gfx/gameFonts/retroGaming.ttf", 25);
    //fontScoreBoard= TTF_OpenFont("gfx/gameFonts/retroGaming.ttf", 20);
    fontScoreBoard= TTF_OpenFont("gfx/gameFonts/DejaVuSans.ttf", 20);
    titleFont= TTF_OpenFont("gfx/gameFonts/retroGaming.ttf", 50);
    if(!font){
        printf("UnableToGetFonts");
    }
    return;
}

void sdlOpenAudio(){
    int audioRate,audioChannel;
    Uint16 audioFormat;
    audioRate = MIX_DEFAULT_FREQUENCY;
    audioFormat = MIX_DEFAULT_FORMAT;
    audioChannel = MIX_DEFAULT_CHANNELS;
    if(Mix_OpenAudio(audioRate,audioFormat,audioChannel,4096)<0){
        SDL_Log("couldn't open audio: %s\n",SDL_GetError());
        printf("audio error");
        Mix_FreeChunk(wave);
    }
    else{
        Mix_QuerySpec(&audioRate,&audioFormat,&audioChannel);
        wave=Mix_LoadWAV("./sfx/jump.wav");
        waveGameEnd=Mix_LoadWAV("./sfx/gameEnd.wav");
    }
    return;
}

void renderAudio(int audio){
    switch (audio) {
        case JUMP_AUDIO_OPT:
            Mix_PlayChannel(MIX_DEFAULT_CHANNELS, wave,0);
        break;
        case GAME_END_AUDIO_OPT:
            Mix_PlayChannel(MIX_DEFAULT_CHANNELS, waveGameEnd,0);
        break;
        default:
        break;
    }
}

// --- Initialize screen ---
void initializeSdl(){
    int gotscreen = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER |
                             SDL_INIT_AUDIO);
    if(gotscreen != 0){
        printf("Not able to initialize window: track 4\n");
        return;
    }
    // Initialize SDL_ttf.
    TTF_Init();
    sdlOpenAudio();
    sdlOpenFont();
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

// *** Initialize screen ***

