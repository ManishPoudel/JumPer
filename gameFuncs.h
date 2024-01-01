#pragma once
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "sdlFuncs.h"
#include "gameVars.h"
// Helper functions.
void setImgVariables();
int getRandInt();
void freeSurface();
void setTilesPos();
void queryTexture();
int isTilesPos(struct Jumper *jumper);
int attachJumperToTiles(struct Jumper *jumper);
void controlMovement(struct Jumper *,int*);
void moveTiles();

// For menu
void startWin();

// main gameplay in jumper.c
void gamePlay(void);

