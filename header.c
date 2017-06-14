#include "header.h"


int init(char *title, int xpos,int ypos,int height, int width,int flags,game *myGame){


    //initialize SDL

    if(SDL_Init(SDL_INIT_EVERYTHING)>=0)
    {
            //if succeeded create our window
            myGame->g_pWindow=SDL_CreateWindow(title,xpos,ypos,height,width,flags);
            //if succeeded create window, create our render
            if(myGame->g_pWindow!=NULL){
                myGame->g_pRenderer=SDL_CreateRenderer(myGame->g_pWindow,-1,SDL_RENDERER_ACCELERATED);
                SDL_SetRenderDrawColor(myGame->g_pRenderer, 0, 0, 0, 255);
                SDL_RenderClear(myGame->g_pRenderer);

            }


    }else{


        return 0;
    }




    return 1;


}


void initBlocks1(mBlock Block[]){

    int i;
    int x;
    int y;


        y = 80;
        x = SCREEN_WIDTH/2-BLOCK_WIDTH*4-BLOCK_WIDTH/2;

        for(i=1;i<=45;i++){

            Block[i].color=rand()%4;
            Block[i].state=1;

            Block[i].x=x;
            Block[i].y=y;


            x+=BLOCK_WIDTH;

            if(i%9==0 && i!=0){
                x=SCREEN_WIDTH/2-BLOCK_WIDTH*4-BLOCK_WIDTH/2;
                y+=BLOCK_HEIGHT;
            }

        }

}


void initBlocks2(mBlock Block[]){

    int i;
    int x;
    int y;


        y = 80;
        x = SCREEN_WIDTH/2+BLOCK_WIDTH;

        for(i=1;i<=16;i++){

            Block[i].color=rand()%4;
            Block[i].state=1;

        }
        //Ligne 1
        Block[1].x = SCREEN_WIDTH/2-BLOCK_WIDTH/2;
        Block[1].y = 80;


        //Ligne 2
        Block[2].x = Block[1].x-BLOCK_WIDTH/2;
        Block[2].y = 80+BLOCK_HEIGHT;

        Block[3].x = Block[2].x+BLOCK_WIDTH;
        Block[3].y = Block[2].y;

        //Ligne 3
        Block[4].x = Block[2].x-BLOCK_WIDTH/2;
        Block[4].y = 80+BLOCK_HEIGHT*2;

        Block[5].x = Block[1].x;
        Block[5].y = Block[4].y;

        Block[6].x = Block[5].x+BLOCK_WIDTH;
        Block[6].y = 80+BLOCK_HEIGHT*2;

        //Ligne 4
        Block[7].x = Block[2].x-BLOCK_WIDTH;
        Block[7].y = 80+BLOCK_HEIGHT*3;

        Block[8].x = Block[7].x+BLOCK_WIDTH;
        Block[8].y = Block[7].y;

        Block[9].x = Block[8].x+BLOCK_WIDTH;
        Block[9].y = Block[7].y;

        Block[10].x = Block[9].x+BLOCK_WIDTH;
        Block[10].y = Block[7].y;

        //Ligne 5

        Block[11].x = Block[7].x-BLOCK_WIDTH/2;
        Block[11].y = 80+BLOCK_HEIGHT*4;

        Block[12].x = Block[11].x+BLOCK_WIDTH;
        Block[12].y = Block[11].y;

        Block[13].x = Block[12].x+BLOCK_WIDTH;
        Block[13].y = Block[11].y;

        Block[14].x = Block[13].x+BLOCK_WIDTH;
        Block[14].y = Block[11].y;

        Block[15].x = Block[14].x+BLOCK_WIDTH;
        Block[15].y = Block[11].y;



}

void ResetBlock(mBlock Block[]){

    int i;

    for(i=0;i<=45;i++){
        Block[i].state=0;
    }


}


void handleEvents(gameState *state, coordonnees *Paddle, mBall *Ball){

    SDL_Event event;

    if(SDL_PollEvent(&event)){
        switch(event.type){
        case SDL_QUIT:
              state->g_bRunning=0;break;
        case SDL_KEYDOWN:
                        switch (event.key.keysym.sym)
                            {
                                case SDLK_ESCAPE: state->g_bRunning=0;break;
                                case SDLK_LEFT:state->left=1;state->right=0;break;
                                case SDLK_RIGHT:state->right=1;state->left=0 ;break;
                                case SDLK_SPACE:Ball->start=1;break;
                            }
                            break;

        case SDL_KEYUP:
                switch (event.key.keysym.sym)
                            {
                                case SDLK_LEFT:state->left=0;break;
                                case SDLK_RIGHT:state->right=0;break;
                            }
                            break;

        default:break;

        }
    }


    if(Ball->start==0){
        Ball->x=Paddle->x+PADDLE_WIDTH/2-BALL_SIZE/2;
    }

    if(Ball->start==1){


        if(Ball->y<=16){
            Ball->up=0;
        }

        if(Ball->y+BALL_SIZE>Paddle->y && Ball->x+BALL_SIZE>=Paddle->x && Ball->x<=Paddle->x+PADDLE_WIDTH && Ball->y+BALL_SIZE<SCREEN_HEIGHT){
            Ball->up=1;

/*
            if(Ball->x+BALL_SIZE < Paddle->x+PADDLE_WIDTH/2){
                Ball->left=1;
                Ball->angle=(Paddle->x - Ball->x+BALL_SIZE) / 64;
            }

            if(Ball->x > Paddle->x+PADDLE_WIDTH/2){
                Ball->left=-1;
                Ball->angle=(Ball->x - Paddle->x+PADDLE_WIDTH/2) / 64;
            }
*/

            if(Ball->x+BALL_SIZE/2<Paddle->x+PADDLE_WIDTH/2-15){
                Ball->left=1;
                Ball->angle=(Paddle->x+PADDLE_WIDTH/2-Ball->x+BALL_SIZE)/100;
            }

            if(Ball->x+BALL_SIZE/2>Paddle->x+PADDLE_WIDTH/2-15 && Ball->x+BALL_SIZE/2<Paddle->x+PADDLE_WIDTH/2+15){
                Ball->left=0;
            }

            if(Ball->x+BALL_SIZE/2>Paddle->x+PADDLE_WIDTH/2+15 ){
                Ball->left=-1;
                Ball->angle=(Ball->x+BALL_SIZE-Paddle->x+PADDLE_WIDTH/2)/100;
            }
        }

        if(Ball->x<=16){
            Ball->left=-1;
        }

        if(Ball->x+BALL_SIZE>=SCREEN_WIDTH-16){
            Ball->left=1;
        }



        if(Ball->up==1){
            Ball->y-=SPEED_BALLE;
        }

        if(Ball->up==0){
            Ball->y+=SPEED_BALLE;
        }

        if(Ball->left==1){
            Ball->x-=SPEED_BALLE/2;
        }

        if(Ball->left==-1){
            Ball->x+=SPEED_BALLE/2;
        }




    }

    if(state->left!=0 && Paddle->x>=16){
        Paddle->x-=SPEED_PADDLE;
    }

    if(state->right!=0 && Paddle->x<=SCREEN_WIDTH-PADDLE_WIDTH-16){
        Paddle->x+=SPEED_PADDLE;
    }

    if(Ball->y-200>SCREEN_HEIGHT){
        state->g_bRunning=0;
    }

}



void DrawPaddle(game *myGame, coordonnees *Paddle){

        SDL_Rect PaddleDest;
        SDL_Rect PaddleSource;



        myGame->g_surface = IMG_Load("./assets/paddle.png");//Chargement de l'image png

        if(!myGame->g_surface) {
            fprintf(stdout,"IMG_Load: %s\n", IMG_GetError());
            // handle error
        }

        if(myGame->g_surface){


                 myGame->g_texture = SDL_CreateTextureFromSurface(myGame->g_pRenderer,myGame->g_surface); // Préparation du sprite
                 SDL_FreeSurface(myGame->g_surface); // Libération de la ressource occupée par le sprite

                if(myGame->g_texture){


                    PaddleSource.x=0;//128*(int)((SDL_GetTicks()/100)%6);
                    PaddleSource.y=0;
                    PaddleSource.w=PADDLE_WIDTH;//1 image = w:128 et h:82
                    PaddleSource.h=PADDLE_HEIGHT;

                    SDL_QueryTexture(myGame->g_texture,NULL,NULL,NULL,NULL);

                    //Définition du rectangle dest pour dessiner Bitmap
                    PaddleDest.x=Paddle->x;//debut x
                    PaddleDest.y=Paddle->y;//debut y
                    PaddleDest.w=PaddleSource.w; //Largeur
                    PaddleDest.h=PaddleSource.h; //Hauteur

                    SDL_RenderCopy(myGame->g_pRenderer,myGame->g_texture,&PaddleSource,&PaddleDest);

                    SDL_RenderPresent(myGame->g_pRenderer); // Affichage

                    SDL_RenderClear(myGame->g_pRenderer);

                }

                else{
                        fprintf(stdout,"Échec de création de la texture (%s)\n",SDL_GetError());
                }




        }else{
            fprintf(stdout,"Échec de chargement du sprite (%s)\n",SDL_GetError());
        }


    destroyTexture(myGame);

}


void DrawBall(game *myGame, mBall *Ball){

        SDL_Rect DestBall;
        SDL_Rect SourceBall;



        myGame->g_surface = IMG_Load("./assets/ball.png");//Chargement de l'image png

        if(!myGame->g_surface) {
            fprintf(stdout,"IMG_Load: %s\n", IMG_GetError());
            // handle error
        }

        if(myGame->g_surface){


                 myGame->g_texture = SDL_CreateTextureFromSurface(myGame->g_pRenderer,myGame->g_surface); // Préparation du sprite
                 SDL_FreeSurface(myGame->g_surface); // Libération de la ressource occupée par le sprite

                if(myGame->g_texture){


                    SourceBall.x=0;//128*(int)((SDL_GetTicks()/100)%6);
                    SourceBall.y=0;
                    SourceBall.w=BALL_SIZE;//1 image = w:128 et h:82
                    SourceBall.h=BALL_SIZE;

                    SDL_QueryTexture(myGame->g_texture,NULL,NULL,NULL,NULL);

                    //Définition du rectangle dest pour dessiner Bitmap
                    DestBall.x=Ball->x;//debut x
                    DestBall.y=Ball->y;//debut y
                    DestBall.w=BALL_SIZE; //Largeur
                    DestBall.h=BALL_SIZE; //Hauteur

                    SDL_RenderCopy(myGame->g_pRenderer,myGame->g_texture,&SourceBall,&DestBall);

                }

                else{
                        fprintf(stdout,"Échec de création de la texture (%s)\n",SDL_GetError());
                }




        }else{
            fprintf(stdout,"Échec de chargement du sprite (%s)\n",SDL_GetError());
        }


    destroyTexture(myGame);

}



void DrawSide1(game *myGame){

        SDL_Rect Side1Source;
        SDL_Rect Side1Dest;


        myGame->g_surface = IMG_Load("./assets/side.png");//Chargement de l'image png

        if(!myGame->g_surface) {
            fprintf(stdout,"IMG_Load: %s\n", IMG_GetError());
            // handle error
        }

        if(myGame->g_surface){


                 myGame->g_texture = SDL_CreateTextureFromSurface(myGame->g_pRenderer,myGame->g_surface); // Préparation du sprite
                 SDL_FreeSurface(myGame->g_surface); // Libération de la ressource occupée par le sprite

                if(myGame->g_texture){




                    Side1Source.x=0;
                    Side1Source.y=0;
                    Side1Source.w=16;
                    Side1Source.h=600;

                    SDL_QueryTexture(myGame->g_texture,NULL,NULL,NULL,NULL);

                    //Définition du rectangle dest pour dessiner Bitmap
                    Side1Dest.x=0;//debut x
                    Side1Dest.y=0;//debut y
                    Side1Dest.w=16; //Largeur
                    Side1Dest.h=SCREEN_HEIGHT; //Hauteur

                    SDL_RenderCopy(myGame->g_pRenderer,myGame->g_texture,&Side1Source,&Side1Dest);

                }

                else{
                        fprintf(stdout,"Échec de création de la texture (%s)\n",SDL_GetError());
                }




        }else{
            fprintf(stdout,"Échec de chargement du sprite (%s)\n",SDL_GetError());
        }


    destroyTexture(myGame);

}

void DrawSide2(game *myGame){

        SDL_Rect Side1Source;
        SDL_Rect Side1Dest;


        myGame->g_surface = IMG_Load("./assets/side.png");//Chargement de l'image png

        if(!myGame->g_surface) {
            fprintf(stdout,"IMG_Load: %s\n", IMG_GetError());
            // handle error
        }

        if(myGame->g_surface){


                 myGame->g_texture = SDL_CreateTextureFromSurface(myGame->g_pRenderer,myGame->g_surface); // Préparation du sprite
                 SDL_FreeSurface(myGame->g_surface); // Libération de la ressource occupée par le sprite

                if(myGame->g_texture){




                    Side1Source.x=0;
                    Side1Source.y=0;
                    Side1Source.w=16;
                    Side1Source.h=600;

                    SDL_QueryTexture(myGame->g_texture,NULL,NULL,NULL,NULL);

                    //Définition du rectangle dest pour dessiner Bitmap
                    Side1Dest.x=SCREEN_WIDTH-16;//debut x
                    Side1Dest.y=0;//debut y
                    Side1Dest.w=16; //Largeur
                    Side1Dest.h=SCREEN_HEIGHT; //Hauteur

                    SDL_RenderCopy(myGame->g_pRenderer,myGame->g_texture,&Side1Source,&Side1Dest);

                }

                else{
                        fprintf(stdout,"Échec de création de la texture (%s)\n",SDL_GetError());
                }




        }else{
            fprintf(stdout,"Échec de chargement du sprite (%s)\n",SDL_GetError());
        }


    destroyTexture(myGame);

}

void DrawSide3(game *myGame){

        SDL_Rect Side1Source;
        SDL_Rect Side1Dest;


        myGame->g_surface = IMG_Load("./assets/top.png");//Chargement de l'image png

        if(!myGame->g_surface) {
            fprintf(stdout,"IMG_Load: %s\n", IMG_GetError());
            // handle error
        }

        if(myGame->g_surface){


                 myGame->g_texture = SDL_CreateTextureFromSurface(myGame->g_pRenderer,myGame->g_surface); // Préparation du sprite
                 SDL_FreeSurface(myGame->g_surface); // Libération de la ressource occupée par le sprite

                if(myGame->g_texture){




                    Side1Source.x=0;
                    Side1Source.y=0;
                    Side1Source.w=600;
                    Side1Source.h=16;

                    SDL_QueryTexture(myGame->g_texture,NULL,NULL,NULL,NULL);

                    //Définition du rectangle dest pour dessiner Bitmap
                    Side1Dest.x=16;//debut x
                    Side1Dest.y=0;//debut y
                    Side1Dest.w=SCREEN_WIDTH-32; //Largeur
                    Side1Dest.h=16; //Hauteur

                    SDL_RenderCopy(myGame->g_pRenderer,myGame->g_texture,&Side1Source,&Side1Dest);

                }

                else{
                        fprintf(stdout,"Échec de création de la texture (%s)\n",SDL_GetError());
                }




        }else{
            fprintf(stdout,"Échec de chargement du sprite (%s)\n",SDL_GetError());
        }


    destroyTexture(myGame);

}


void DrawBlock(game *myGame,mBlock Block[], int NbBlocks){

        SDL_Rect Source;
        SDL_Rect Dest;

        int i;


        for(i=1;i<=NbBlocks;i++){

            if(Block[i].state!=0){

                            myGame->g_surface = IMG_Load("./assets/bricks.png");//Chargement de l'image png

            if(!myGame->g_surface) {
                fprintf(stdout,"IMG_Load: %s\n", IMG_GetError());
                // handle error
            }

            if(myGame->g_surface){


                     myGame->g_texture = SDL_CreateTextureFromSurface(myGame->g_pRenderer,myGame->g_surface); // Préparation du sprite
                     SDL_FreeSurface(myGame->g_surface); // Libération de la ressource occupée par le sprite

                    if(myGame->g_texture){

                        switch(Block[i].color){

                            case 0:
                                Source.x=0;
                                Source.y=0;
                                Source.w=BLOCK_WIDTH;
                                Source.h=BLOCK_HEIGHT;
                                break;

                            case 1:
                                Source.x=64;
                                Source.y=0;
                                Source.w=BLOCK_WIDTH;
                                Source.h=BLOCK_HEIGHT;
                                break;

                            case 2:
                                Source.x=0;
                                Source.y=24;
                                Source.w=BLOCK_WIDTH;
                                Source.h=BLOCK_HEIGHT;
                                break;

                            case 3:
                                Source.x=64;
                                Source.y=24;
                                Source.w=BLOCK_WIDTH;
                                Source.h=BLOCK_HEIGHT;
                                break;


                        }

                        SDL_QueryTexture(myGame->g_texture,NULL,NULL,NULL,NULL);

                        //Définition du rectangle dest pour dessiner Bitmap
                        Dest.x=Block[i].x;//debut x
                        Dest.y=Block[i].y;//debut y
                        Dest.w=BLOCK_WIDTH; //Largeur
                        Dest.h=BLOCK_HEIGHT; //Hauteur

                        SDL_RenderCopy(myGame->g_pRenderer,myGame->g_texture,&Source,&Dest);

                    }

                    else{
                            fprintf(stdout,"Échec de création de la texture (%s)\n",SDL_GetError());
                    }




            }else{
                fprintf(stdout,"Échec de chargement du sprite (%s)\n",SDL_GetError());
            }

            destroyTexture(myGame);





            }
        }
}



void delay(unsigned int frameLimit){
    // Gestion des 60 fps (images/seconde)
    unsigned int ticks = SDL_GetTicks();

    if (frameLimit < ticks)
    {
        return;
    }

    if (frameLimit > ticks + 16)
    {
        SDL_Delay(16);
    }

    else
    {
        SDL_Delay(frameLimit - ticks);
    }
}


void colllisionBlocks(mBlock Block[], mBall *Ball){
    int i;

    for(i=1;i<=45;i++){

        if(Block[i].state==1){


            if(Ball->y+BALL_SIZE>Block[i].y && Ball->y<Block[i].y+BLOCK_HEIGHT){

                if(Ball->x+BALL_SIZE>Block[i].x && Ball->x+BALL_SIZE<Block[i].x+5){
                    Ball->left=1;
                    Block[i].state=0;
                }

                if(Ball->x<Block[i].x+BLOCK_WIDTH && Ball->x>Block[i].x+BLOCK_WIDTH-5){
                    Ball->left=-1;
                    Block[i].state=0;
                }

            }

            if(Ball->x+BALL_SIZE>Block[i].x && Ball->x<Block[i].x+BLOCK_WIDTH){

                if(Ball->y<Block[i].y+BLOCK_HEIGHT && Ball->y>Block[i].y+BLOCK_HEIGHT/2){
                    Ball->up=0;
                    Block[i].state=0;
                }

                if(Ball->y+BALL_SIZE>Block[i].y && Ball->y+BALL_SIZE<Block[i].y+BLOCK_HEIGHT/2){
                    Ball->up=1;
                    Block[i].state=0;
                }
            }
        }
    }
}




void destroy(game *myGame){

    //Destroy render
    if(myGame->g_pRenderer!=NULL)
        SDL_DestroyRenderer(myGame->g_pRenderer);


    //Destroy window
    if(myGame->g_pWindow!=NULL)
        SDL_DestroyWindow(myGame->g_pWindow);

}



void destroyTexture(game *myGame){

    //Destroy texture
    if(myGame->g_texture!=NULL)
            SDL_DestroyTexture(myGame->g_texture);


}

