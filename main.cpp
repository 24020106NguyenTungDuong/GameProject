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
    srand(time(0));
    if(SDL_Init(SDL_INIT_VIDEO)!=0)
    {
        cout<<"SDL_Init failed. Error:"<<SDL_GetError<<endl;
    }
    if(!IMG_Init(IMG_INIT_PNG))
    {
        cout<<"IMG_Init failed. Error:"<<IMG_GetError()<<endl;
    }

    inputMap(centerMap,mapList[0]);
    inputMap(rightMap,mapList[rand()%numberOfMaps]);
    inputMap(leftMap,mapList[rand()%numberOfMaps]);

    RenderWindow window("Game 1",screenWidth,screenHeight);
    SDL_Texture* testTexture=window.LoadTexture("res/graphics/playerSprite/player24 - Copy.png");
    SDL_Texture* slashTexture=window.LoadTexture("res/graphics/playerSprite/slash.png");
    SDL_Texture* Cursor=window.LoadTexture("res/graphics/playerSprite/cursor.png");


    Player player0(vector2f(9680,500),playerWidth,playerHeight,testTexture);
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


    SDL_Texture* enemy=window.LoadTexture("res/graphics/EnemySprite/0.png");
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

        for(vector <Enemy>::iterator it=Enemies.begin();it!= Enemies.end();)
            {
                if (it->HP<=0||abs(it->chunkNumber-player0.chunkNumber)>1)
                        {
                            it=Enemies.erase(it);
                        }
                        else
                        {
                            ++it;
                        }
            }

          for(int i=0;i<Enemies.size();i++)
        {
            Enemies[i].collisionPlayer(player0,slashing);
            Enemies[i].updateEnemy(player0,currentTime,timeAcumulator);

            //if(player0.HP<=0) gameRunning=0;
        }
        //updateRightMap when enter new right map
        if(int(player0.position.x/screenWidth)>player0.chunkNumber)
            {player0.chunkNumber++;
                swap(centerMap,leftMap);
                swap(centerChunk,leftChunk);
                swap(centerMap,rightMap);
                swap(centerChunk,rightChunk);
    inputMap(rightMap,mapList[rand()%numberOfMaps]);
        loadChunk(rightMap,greenBrick,platform,rightChunk,1,player0.chunkNumber);
                        //spawn Enemy when enter new right map
                         for(int y=1;y<mapTileHeight-1;y++)
                            for(int x=1;x<mapTileWidth-1;x++)
                            {
                                if(rightMap[y][x]!=0&&rightMap[y-1][x-1]==0&&rightMap[y-1][x]==0&&rightMap[y-1][x+1]==0)
                                if(rand()%100<= spawnRate*100)
                                {
                                    vector2f newEnemyPosition;
                                    newEnemyPosition.x=x*tileSize+(player0.chunkNumber+1)*screenWidth;
                                    newEnemyPosition.y=y*tileSize-entityScalar*enemyHeight;
                                    Enemies.push_back(Enemy(newEnemyPosition,enemyWidth,enemyHeight,enemy));
                                    if(x+5<mapTileWidth) x+=5;
                                    else break;
                                }


                            }
            }
        //updateLeftMap when enter new left map
         if(int(player0.position.x/screenWidth)<player0.chunkNumber)
            {
                player0.chunkNumber--;
                swap(leftMap,centerMap);
                swap(leftChunk,centerChunk);
                swap(leftMap,rightMap);
                swap(leftChunk,rightChunk);
                inputMap(leftMap,mapList[rand()%numberOfMaps]);
                loadChunk(leftMap,greenBrick,platform,leftChunk,-1,player0.chunkNumber);
            }



        player0.checkTileCollision(centerMap);

        slashing.updateProj(timeAcumulator);

        Cam.updateCamera(player0);

        window.ClearScreen();
        window.renderBackGround();
        window.renderChunk(Cam,leftChunk,centerChunk,rightChunk);
        window.RenderTexture(player0,Cam);

                for(int i=0;i<Enemies.size();i++)
        {
            Enemies[i].keepOnPlatForm(player0,leftMap,centerMap,rightMap);
            window.RenderTexture(Enemies[i],Cam);
        }

        if(slashing.active) window.RenderTexture(slashing,Cam);
        window.Display();
        SDL_Delay(1000/FPS);
    }




    window.CleanUp();

    return 0;
}
