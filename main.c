#include "header.h"


//Option de build dans les linker setting mettre les libSDL2main.a libSDL2.dll.a
//Dans search directory
//Option de build compiler mettre les include
//Option de build linker mettre les lib

//mettre dans build linker -lmingw32


int main(int argc, char *argv[])
{

     game myGame;
     gameState state;
     mBall Ball;

     mBlock Block[46];

     coordonnees Paddle;

     int NbBlocks=45;
     int i;
     int alldestroyed = 0;

    //Pour les 60 fps
    unsigned int frameLimit = SDL_GetTicks() + 16;

    if(init("BrickBreaker",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN,&myGame)){

                state.g_bRunning=1;


    }else{

            return 1;//something's wrong

    }




    srand(time(NULL));   //Init du random
    Ball.left=0;   //Random si la balle part à gauche où droite
    state.right=0;
    state.left=0;
    Paddle.x=SCREEN_WIDTH/2-PADDLE_WIDTH/2;
    Paddle.y=SCREEN_HEIGHT-PADDLE_HEIGHT;
    Ball.x=SCREEN_WIDTH/2-BALL_SIZE/2;
    Ball.y=SCREEN_HEIGHT-100;
    Ball.start=0;
    Ball.up=1;

    initBlocks1(Block);

    while(state.g_bRunning){

            for(i=1;i<=NbBlocks;i++){
                if(Block[i].state==1){
                    alldestroyed=0;
                    break;
                }else alldestroyed=1;
            }

            if(alldestroyed==1){
                ResetBlock(Block);
                NbBlocks=15;
                Ball.Destroyed=0;
                Ball.up = 1;
                Ball.left = 0;
                Ball.start=0;
                Ball.y = SCREEN_HEIGHT-100;
                initBlocks2(Block);
            }

           colllisionBlocks(Block, &Ball);
           handleEvents(&state,&Paddle,&Ball);
           DrawSide1(&myGame);
           DrawSide2(&myGame);
           DrawSide3(&myGame);
           DrawPaddle(&myGame,&Paddle);
           DrawBlock(&myGame,Block, NbBlocks);
           DrawBall(&myGame,&Ball);


        // Gestion des 60 fps (1000ms/60 = 16.6 -> 16
            delay(frameLimit);
            frameLimit = SDL_GetTicks() + 16;


    }

        destroy(&myGame);

        SDL_Quit();




  return 0;
}

