#include <iostream>
#define SDL_MAIN_HANDLED
#include<SDL.h>
#include <SDL_image.h>
#include<vector>
#include <ctime>
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "utils.hpp"
#include "constants.hpp"
#include "Player.hpp"
#include "camera.hpp"
#include "chunkMap/chunkMap.hpp"
#include "Enemy.hpp"
using namespace std;


int main(int argc, char *argv[])
{

    inputMap(centerMap,mapList[0]);
    inputMap(rightMap,mapList[rand()%4]);
    inputMap(leftMap,mapList[rand()%4]);
    srand(time(0));
    if(SDL_Init(SDL_INIT_VIDEO)!=0)
    {
        cout<<"SDL_Init failed. Error:"<<SDL_GetError<<endl;
    }
    if(!IMG_Init(IMG_INIT_PNG))
    {
        cout<<"IMG_Init failed. Error:"<<IMG_GetError()<<endl;
    }
    RenderWindow window("Game 1",screenWidth,screenHeight);
    SDL_Texture* testTexture=window.LoadTexture("res/graphics/playerSprite/player24 - Copy.png");
    SDL_Texture* slashTexture=window.LoadTexture("res/graphics/playerSprite/slash - Copy.png");


    Player player0(vector2f(9650,500),playerWidth,playerHeight,testTexture);
    Projectile slashing(vector2f(0,0),slashWidth,slashHeight,slashTexture);

    Player player1=player0;
    player1.position.x+=50;

    player0.chunkNumber=player0.position.x/screenWidth;
    camera Cam;


    SDL_Texture* greenBrick=window.LoadTexture("res/graphics/tileMap/solidTile.png");
    SDL_Texture* platform=window.LoadTexture("res/graphics/tileMap/platform.png");


     loadChunk(centerMap,greenBrick,platform,centerChunk,0,player0.chunkNumber);
        loadChunk(rightMap,greenBrick,platform,rightChunk,1,player0.chunkNumber);
        loadChunk(leftMap,greenBrick,platform,leftChunk,-1,player0.chunkNumber);


    SDL_Texture* enemy=window.LoadTexture("res/graphics/EnemySprite/1.png");
    Enemy enemy0=Enemy(vector2f(10000,559),24,24,enemy);
    Enemy enemy1=enemy0;

    bool gameRunning=1;
    bool pause=0;

    SDL_Event event;

    float startLoopTime=utils::getTimeSeconds();
    float currentTime=0.0f;
    float timeAcumulator=0.0f;
    while(gameRunning)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type==SDL_QUIT)
                gameRunning=0;
                if(event.type==SDL_KEYDOWN&&event.key.keysym.sym==SDLK_ESCAPE)
                {
                    pause=!pause;
                }

        }
        if(pause==1) continue;

        //get time

        currentTime = utils::getTimeSeconds();
        timeAcumulator += currentTime-startLoopTime;
        startLoopTime = currentTime;
        if(timeAcumulator>=1.0f) timeAcumulator-=1.0f;


        const Uint8* keystates = SDL_GetKeyboardState(NULL);

       int mouseX, mouseY;
        Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);

        player0.updatePlayer(keystates,event, mouseState,mouseX,mouseY, slashing ,timeAcumulator,Cam);

        enemy0.updateEnemy(player0,currentTime,timeAcumulator);
        enemy1.updateEnemy(player0,currentTime,timeAcumulator);
        //updateRightMap when enter new right map
        if(int(player0.position.x/screenWidth)>player0.chunkNumber)
            {player0.chunkNumber++;
                swap(centerMap,leftMap);
                swap(centerChunk,leftChunk);
                swap(centerMap,rightMap);
                swap(centerChunk,rightChunk);
    inputMap(rightMap,mapList[rand()%4]);
        loadChunk(rightMap,greenBrick,platform,rightChunk,1,player0.chunkNumber);
            }
        //updateLeftMap when enter new left map
         if(int(player0.position.x/screenWidth)<player0.chunkNumber)
            {
                player0.chunkNumber--;
                swap(leftMap,centerMap);
                swap(leftChunk,centerChunk);
                swap(leftMap,rightMap);
                swap(leftChunk,rightChunk);
                inputMap(leftMap,mapList[rand()%4]);
                loadChunk(leftMap,greenBrick,platform,leftChunk,-1,player0.chunkNumber);
            }

        player0.checkTileCollision(centerMap);


        enemy0.keepOnPlatForm(player0,leftMap,centerMap,rightMap);

        slashing.updateProj(timeAcumulator);

        Cam.updateCamera(player0);

        window.ClearScreen();
        window.renderChunk(Cam,leftChunk,centerChunk,rightChunk);
        window.RenderTexture(player0,Cam);
        window.RenderTexture(enemy0,Cam);
        //window.RenderTexture(enemy1,Cam);
        if(slashing.active) window.RenderTexture(slashing,Cam);
        window.Display();
        SDL_Delay(1000/FPS);
    }




    window.CleanUp();

    return 0;
}
