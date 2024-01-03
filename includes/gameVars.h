#pragma once

#define WINDOW_WIDTH 680
#define WINDOW_HEIGHT 400
#define JUMP_DISTANCE 140
#define JUMPER_WIDTH    54
 //Since scaled down in setImgVariable()(srcImg.h/=2).
#define JUMPER_HEIGHT   32


//Main Character which jumps.
struct Jumper{
    int x_pos;  // Positions of jumper.
    int y_pos;
    int speed;  // Speed of jumper Movements.
    int jumpHeight; //Height up to which jumper jumps.
    int up, left, right, down;    //Control direction of jumper.
};
