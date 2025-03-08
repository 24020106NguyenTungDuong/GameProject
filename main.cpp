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
using namespace std;

int mapTile[mapTileHeight][mapTileWidth];
//{
//{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//{1,0,1,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0,1,2,2,2,2,2,1,0,0,0,1},
//{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//{1,0,0,0,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,0,0,0,1},
//{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,1,0,1},
//{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//{1,0,0,0,0,0,0,0,2,2,2,2,1,1,1,1,1,1,2,2,2,0,0,0,0,0,0,0,0,1},
//{1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1},
//{1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
//{0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//{1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//};


int main(int argc, char *argv[])
{
    string mapList[4]={"res/mapList/map1.txt","res/mapList/map2.txt","res/mapList/map3.txt","res/mapList/map4.txt"};
    inputMap(centerMap,mapList[0]);
    inputMap(rightMap,mapList[rand()%4]);
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


    Player player0(vector2f(32,500),testTexture);
    Projectile slashing(vector2f(0,0),slashTexture);

    camera Cam;


    SDL_Texture* greenBrick=window.LoadTexture("res/graphics/tileMap/solidTile.png");
    SDL_Texture* platform=window.LoadTexture("res/graphics/tileMap/platform.png");

     loadChunk(centerMap,greenBrick,platform,centerChunk,0,player0.chunkNumber);
        loadChunk(rightMap,greenBrick,platform,rightChunk,1,player0.chunkNumber);
        loadChunk(leftMap,greenBrick,platform,leftChunk,-1,player0.chunkNumber);



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

        currentTime = utils::getTimeSeconds();
        timeAcumulator += currentTime-startLoopTime;
        startLoopTime = currentTime;
        if(timeAcumulator>=1.0f) timeAcumulator-=1.0f;


        const Uint8* keystates = SDL_GetKeyboardState(NULL);

       int mouseX, mouseY;
        Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);

        player0.updatePlayer(keystates,event, mouseState,mouseX,mouseY, slashing ,timeAcumulator,Cam);




        if(int(player0.position.x/screenWidth)>player0.chunkNumber)
            {player0.chunkNumber++;
                swap(centerMap,leftMap);
                swap(centerMap,rightMap);
    inputMap(rightMap,mapList[rand()%4]);
     loadChunk(centerMap,greenBrick,platform,centerChunk,0,player0.chunkNumber);
        loadChunk(rightMap,greenBrick,platform,rightChunk,1,player0.chunkNumber);
        //loadChunk(leftMap,greenBrick,platform,leftChunk,-1,player0.chunkNumber);
            }
         if(int(player0.position.x/screenWidth)<player0.chunkNumber)
            {player0.chunkNumber--;
                swap(rightMap,centerMap);
            }

        player0.checkTileCollision(centerMap);

        slashing.updateProj(timeAcumulator);

        Cam.updateCamera(player0);



        window.ClearScreen();
//        for(int i=0;i<centerChunk.size();i++)
//        {
//            window.RenderMap(centerChunk[i],Cam);
//        }
//
//         for(int i=0;i<rightChunk.size();i++)
//        {
//            window.RenderMap(rightChunk[i],Cam);
//        }
//            for(int i=0;i<leftChunk.size();i++)
//        {
//            window.RenderMap(leftChunk[i],Cam);
//        }
        window.renderChunk(Cam,leftChunk,centerChunk,rightChunk);
        window.RenderTexture(player0,Cam);
        if(slashing.active) window.RenderTexture(slashing,Cam);
        window.Display();
        SDL_Delay(1000/FPS);
    }




    window.CleanUp();

    return 0;
}
