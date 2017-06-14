#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include <math.h>


#define SPEED_PADDLE 5
#define SPEED_BALLE 5

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 780
#define PADDLE_WIDTH 128
#define PADDLE_HEIGHT 32
#define BALL_SIZE 24
#define BLOCK_WIDTH 64
#define BLOCK_HEIGHT 24



typedef struct game{


     SDL_Window *g_pWindow;
     SDL_Renderer *g_pRenderer;
     SDL_Texture *g_texture;
     SDL_Surface *g_surface;


}game;


typedef struct gameState{

    int g_bRunning;
    int left;
    int right;


}gameState;


typedef struct coordonnees{

    double x;
    double y;



}coordonnees;


typedef struct mBall{

    double x;
    double y;
    int left;
    int up;
    int start;
    float angle;

    int Destroyed;

}mBall;


typedef struct mBlock{

    double x;
    double y;
    int color;
    int state;

}mBlock;






int init(char *title, int xpos,int ypos,int height, int width,int flags,game *myGame);
void handleEvents(gameState *state, coordonnees *Paddle, mBall *Ball);
void DrawPaddle(game *myGame, coordonnees *Paddle);
void DrawBall(game *myGame, mBall *Ball);
void delay(unsigned int frameLimit);
void destroyTexture(game *myGame);
void destroy(game *myGame);


void DrawSide1(game *myGame);
void DrawSide2(game *myGame);
void DrawSide3(game *myGame);
void DrawBlock(game *myGame,mBlock Block[], int NbBlocks);
void initBlocks1(mBlock Block[]);
void initBlocks2(mBlock Block[]);
void colllisionBlocks(mBlock Block[], mBall *Ball);
void ResetBlock(mBlock Block[]);


#endif // HEADER_H_INCLUDED
