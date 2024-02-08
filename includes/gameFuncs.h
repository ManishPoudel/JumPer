#pragma once
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


// For menu
void selectMenu(int *closeReq);

// main gameplay in jumper.c
void gamePlay(void);

