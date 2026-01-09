#include "../includes/gameFuncs.h"

int attachJumperToTiles(struct Jumper *jumper){
    if(isTilesPos(jumper)){
        //jumper->y_pos=tileImg[jumper->jumperTile].y;
        jumper->y_pos += 1;
        // This down is done to move the jumper down
        // along with the tiles.
        jumper->down = 1;
        return 1;
    }
    return 0;
}

void playAudio(int selectAudio){
    renderAudio(selectAudio);
        return;
}

// initialize variables here if needed.
void initializeGameVar(){
    // for random tiles position.
    srand((unsigned)time(NULL));
    // For Menu texts and scores.
    // For title text
    destTextRect[0].x = 210;
    destTextRect[0].y = 100;
    // "StartGame" pos
    destTextRect[1].x = 235;
    destTextRect[1].y = 247;
    // "use < arrow"
    destTextRect[2].x = 220;
    destTextRect[2].y = 190;
    // "Exit" pos
    destTextRect[3].x = 235;
    destTextRect[3].y = 290;
    // for score board.
    destTextRect[5].x = 1;
    destTextRect[5].y = 160;
    return;
}

void selectMenu(int *closeReq){
    int up, down, enter, right,optChoice=0;
    drawMenuRect();
    drawMenuTexts();
    getInput(&enter, &right, &up, &down, closeReq);
    drawSelectBoxMenu(&right, &up, &down,&optChoice);
    if(optChoice==2){
        // 2 is close req
        *closeReq=1;
    }else if(optChoice==1){
        //4 is restart
        *closeReq=4;
    }
    return;
}

int isTilesPos(struct Jumper *jumper){
    for(int i = 0;i < 6;i++){
        if(jumper->x_pos + JUMPER_WIDTH >= tileImg[i].x + 2 &&
            jumper->x_pos <= (tileImg[i].x + TILE_WIDTH) &&
            ((jumper->y_pos + JUMPER_HEIGHT) >= (tileImg[i].y -8) &&
            (jumper->y_pos + JUMPER_HEIGHT) <= tileImg[i].y) ||
            jumper->y_pos==tileImg[i].y && jumper->x_pos==tileImg[i].x ){
            jumper->jumperTile=i;
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
    bgImg.y = ((bgImg.y - 1) % (WINDOW_HEIGHT));
    bgImgPtr.y = (((bgImg.y) + (WINDOW_HEIGHT)));
    return;
}

// jumping is done by this.
void controlMovement(struct Jumper *jumper, int *quitGame){
    int  x_speed = abs(jumper->speed);
    getInput(&jumper->left, &jumper->right, &jumper->up, &jumper->down, quitGame);

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
        // for stopping the jumper at window width we multiply.
        jumper->x_pos += x_speed *
            ((jumper->x_pos + x_speed) < WINDOW_WIDTH - srcImg.w) - 1;
    }
    if(jumper->left == 1){
        /* if(!jumper->up){
            jumper->speed = 6;
        } */
        jumper->x_pos -= x_speed *
            (jumper->x_pos - x_speed > srcImg.w - 38) - 1;
    }
    // now move the jumper picture according to our entity.
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
    bgImgPtr = bgImg;
    bgImg.x = 0;
    bgImg.y = 0;
    bgImgPtr.x = 0;
    bgImgPtr.y = WINDOW_HEIGHT;
    return;
}

void scoreBoard(int score){
 //   int tempScore=0,i;
 //   char scoreChar[20],tempChar;
 //
 //   // convert int score to char
 //   for(i=0;score;i++){
 //       tempScore=score%10;
 //       score=score/10;
 //       scoreChar[i]=tempScore+'0';
 //   }
 //   // reversing string since string is stored in reverse order here.
 //   for(int z=0;z<((i)/2);z++){
 //       tempChar=scoreChar[z];
 //       scoreChar[z]=scoreChar[i-1-z];
 //       scoreChar[i-1-z]=tempChar;
 //   }
 //   scoreChar[i]='\0';
    char scoreChar[20];
    sprintf(scoreChar,"Score:%d",score);
    printScoreBoard(scoreChar);
    return;
}
