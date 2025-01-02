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
    int closeReq = 0,gamePause = 1; // if 1 then game exits.
    // For SDl function intializaiton.
    int topTilesPos=tileImg[0].y;
    int score=0;
    // Audio play flags, better make a struct next time.
    int playedJumpAudio,playedEndAudio=0;
    float floatScore=0.00;
    createSurfaceAndTexture();
    queryTexture();
    setImgVariables();
    setBackgndPos();
    setTilesPos();

    //Our Character.
    struct Jumper jumper = { 0,0,6,JUMP_DISTANCE,0,0,0,0 };

    // Main Game Loop
    while(!(closeReq==1)){
        if(gamePause){
                // play game end audio
                if(!playedEndAudio){
                    playAudio(GAME_END_AUDIO_OPT);
                    playedEndAudio=1;
                }
            // in menu too we need to clear the renderer
            // and so as to mimic out of game ,we do not change
            // the backgnd video positions ,by rendering game first.
            renderCopyGamePlay();
            selectMenu(&closeReq);
            if(closeReq==4){
                // restart game by placing the jumper on the top 
                // tiles.
                for(int x=0;x<6;x++){
                    for(int i=0;i<6;i++){
                        if(tileImg[i].y<topTilesPos){
                            topTilesPos=i;
                        }
                    }
                }
                // if StartGame selected then the jumper position
                // isis set to the top tile position.
                jumper.x_pos=tileImg[topTilesPos].x+10;
                jumper.y_pos=tileImg[topTilesPos].y-srcImg.h;
                floatScore=0;
                gamePause=0;
                closeReq=0;
            }

        } else{
            imgPtr = standImg;
            gamePause = jumper.y_pos >= WINDOW_HEIGHT - srcImg.h;
            playedEndAudio=0;
            moveTiles();
            moveBackgnd();
            if(attachJumperToTiles(&jumper)){
                floatScore+=0.03;
                score=floatScore;
                if(!playedJumpAudio){
                    playAudio(JUMP_AUDIO_OPT);
                    playedJumpAudio=1;
                }
            } else {
                playedJumpAudio=0;
            }
            scoreBoard(score);
            controlMovement(&jumper, &closeReq);
            renderCopyGamePlay();
        }
        renderFunc();
        SDL_Delay(1000 / 60);
    }
    return;
}
//  THATS ALL.  THANK YOU!! :-D
