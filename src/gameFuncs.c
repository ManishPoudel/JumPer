#include "../includes/gameFuncs.h"

int attachJumperToTiles(struct Jumper *jumper){
    if(isTilesPos(jumper)){
        jumper->y_pos += 1;
        // This down is done to move the jumper down
        // along with the tiles.
        jumper->down = 1;
    }
    return 1;
}

// initialize variables here if needed.
void initializeGameVar(){
    srand((unsigned)time(NULL));
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


void moveTiles(){
    for(int i = 0;i < 6;i++){
        tileImg[i].y = (tileImg[i].y + 1) % 400;
        if(tileImg[i].y == 0){
            tileImg[i].x = getRandInt();
        }
    }
    return;
}

void moveBackgnd(){
    bgImg.y=((bgImg.y-1)%(WINDOW_HEIGHT)) ;
    bgImgPtr.y=(((bgImg.y)+(WINDOW_HEIGHT)));
    return;
}

// jumping is done by this.
void controlMovement(struct Jumper *jumper,int *quitGame){
    int  x_speed = abs(jumper->speed);
    getInput(&jumper->left, &jumper->right, &jumper->up, &jumper->down,quitGame);

    if(jumper->up == 1 && !jumper->down /* && !isTilesPos(jumper) */){
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

int getRandInt(){   //Returns random for X position of tile.
    return rand() % 616;
}
void setImgVariables(){
    // for offsetting the positions of the sprites.
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
    for(int i = 0;i < 6;i++){
        tileImg[i].x = getRandInt();
        tileImg[i].y = (i + 1) * 70;
    }
    return;
}

void setBackgndPos(){
    bgImgPtr=bgImg;
    bgImg.x=0;
    bgImg.y=0;
    bgImgPtr.x=0;
    bgImgPtr.y=WINDOW_HEIGHT;
    return;
}
