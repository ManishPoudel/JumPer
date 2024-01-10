#include "../includes/gameFuncs.h"
#include "../includes/gameVars.h"
//For error handeling.

int main(){
    initializeSdl();
    initializeGameVar();
    createWindowRenderer(WINDOW_WIDTH, WINDOW_HEIGHT);
    gamePlay();
    closeAll();
    return 0;
}

//Main game play loop is this.
void gamePlay(void){
    int closeReq=0; // if 1 then game exits.
    // For SDl function intializaiton.
    createSurfaceAndTexture();
    queryTexture();
    setImgVariables();
    setBackgndPos();
    setTilesPos();

    int x_pos = tileImg[1].x + 10;
    int y_pos = tileImg[1].y - srcImg.h;
    srcImg.x = x_pos;
    srcImg.y = y_pos;

    //Our Character.
    struct Jumper jumper = { x_pos,y_pos,6,JUMP_DISTANCE,0,0,0,0 };
    while(!closeReq){
        imgPtr = standImg;
        closeReq = jumper.y_pos >= WINDOW_HEIGHT - srcImg.h;
        moveTiles();
        moveBackgnd();
        attachJumperToTiles(&jumper);
        controlMovement(&jumper,&closeReq);
        renderCopy();
        selectMenu();
        renderFunc();
        SDL_Delay(1000 / 60);
    }
    return;
}

//  THATS ALL.  THANK YOU!! :-D
