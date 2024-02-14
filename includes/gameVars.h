#ifndef vars_initialized
#define vars_initialized
//pixel infor of the generated window.
#define WINDOW_WIDTH 680
#define WINDOW_HEIGHT 400
#define JUMP_DISTANCE 140
#define JUMPER_WIDTH    54
 //Since scaled down in setImgVariable()(srcImg.h/=2).
#define JUMPER_HEIGHT   32

#define JUMP_AUDIO_OPT 1
#define GAME_END_AUDIO_OPT 2

#define TILE_WIDTH 60

//Main Character which jumps.
struct Jumper{
    int x_pos;  // Positions of jumper.
    int y_pos;
    int speed;  // Speed of jumper Movements.
    int jumpHeight; //Height up to which jumper jumps.
    int up, left, right, down;    //Control direction of jumper.
    // -1 if not in tile, else the tile number it is in.
    int jumperTile;     
};

#endif
