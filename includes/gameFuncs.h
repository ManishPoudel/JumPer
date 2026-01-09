#ifndef game_is_on
#define game_is_on
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "gameVars.h"
#include "sdlFuncs.h"

// Helper functions.
void initializeGameVar();
void setImgVariables();
int getRandInt();
void freeSurface();
void setTilesPos();
void setBackgndPos();
int isTilesPos(struct Jumper *jumper);
int attachJumperToTiles(struct Jumper *jumper);
void controlMovement(struct Jumper *, int *);
void moveTiles();

void moveBackgnd();

void scoreBoard(int score);

// For menu
void selectMenu(int *closeReq); 

void playAudio(int selectAudio);
// main gameplay in jumper.c
void gamePlay(void);

#endif
