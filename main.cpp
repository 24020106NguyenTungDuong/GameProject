#include <iostream>
#define SDL_MAIN_HANDLED
#include<SDL.h>
#include<SDL_ttf.h>
#include <SDL_image.h>
#include<vector>
#include<string>
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
        return 1;
    }
    if(!IMG_Init(IMG_INIT_PNG))
    {
        cout<<"IMG_Init failed. Error:"<<IMG_GetError()<<endl;
        return 1;
    }
    if (TTF_Init()==-1) {
        cout<<"SDL_ttf Init failed: "<<TTF_GetError()<<endl;
        return 1;
    }


    RenderWindow window("Game 1",screenWidth,screenHeight);
    SDL_Texture* testTexture=window.LoadTexture("res/graphics/playerSprite/player24 - Copy.png");
    SDL_Texture* slashTexture=window.LoadTexture("res/graphics/playerSprite/slash.png");
    SDL_Texture* Cursor=window.LoadTexture("res/graphics/playerSprite/cursor.png");
    SDL_ShowCursor(SDL_DISABLE);


    TTF_Font* font = TTF_OpenFont("res/font/8bitOperatorPlus-Regular.ttf", 24);
    if (!font) {
        cout <<"Font loading failed:"<<TTF_GetError()<<endl;
        return 1;
    }








    GameStart:

        inputMap(centerMap,mapList[0]);
    inputMap(rightMap,basePath+to_string(rand()%numberOfMaps)+".txt");

    Player player0(playerStartPosition,playerWidth,playerHeight,testTexture);
    Projectile slashing(vector2f(0,0),slashWidth,slashHeight,slashTexture);

    player0.chunkNumber=player0.position.x/screenWidth;
    camera Cam;


    SDL_Texture* greenBrick=window.LoadTexture("res/graphics/tileMap/solidTile.png");
    SDL_Texture* platform=window.LoadTexture("res/graphics/tileMap/platform.png");


     loadChunk(centerMap,greenBrick,platform,centerChunk,0,player0.chunkNumber);
        loadChunk(rightMap,greenBrick,platform,rightChunk,1,player0.chunkNumber);
        loadChunk(leftMap,greenBrick,platform,leftChunk,-1,player0.chunkNumber);


    SDL_Texture* enemy=window.LoadTexture("res/graphics/EnemySprite/0.png");
    bool gameRunning=1;
    bool endScreen=1;
    bool pause=0;
    int frameCount=0;
    int currentFPS=60;
    int currentScore=0;
    int highScore=0;
    int enemiesKilled=0;
    int distanceTravelled=0;
    ifstream file("res/highScore.txt");
    if(file)
    {
        file>>highScore;
    }
    file.close();

    SDL_Event event;

    float startLoopTime=utils::getTimeSeconds();
    float currentTime=0.0f;
    float timeAcumulator=0.0f;
    float frameTime=0;


    while(gameRunning)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type==SDL_QUIT)
                {
                    gameRunning=0;
                    endScreen=0;
                    break;
                }
                if(event.type==SDL_KEYDOWN&&event.key.keysym.sym==SDLK_ESCAPE)
                {
                    pause=!pause;
                }
                if(pause&&event.type==SDL_KEYDOWN&&event.key.keysym.sym==SDLK_r)
                    goto GameStart;

        }
        if(pause==1) {
                window.renderText("Press ESC to resume",vector2f(screenWidth/2-100,screenHeight/2));
                window.renderText("Press R to restart",vector2f(screenWidth/2-100,screenHeight/2+24));
                window.Display();
                continue;
                    }

        currentTime=utils::getTimeSeconds();
        frameTime=currentTime-startLoopTime;
        if(frameTime<frameDelay)
        {
            SDL_Delay(frameDelay-frameTime);
        }
        frameTime=currentTime-startLoopTime;
        timeAcumulator+=frameTime;
        startLoopTime=currentTime;
        frameCount++;
        if(timeAcumulator>=1.0f) {timeAcumulator-=1.0f;
                                    currentFPS=frameCount;
                                    frameCount=0;
                                    }

        const Uint8* keystates = SDL_GetKeyboardState(NULL);

       int mouseX, mouseY;
        Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);

        player0.updatePlayer(keystates,event, mouseState,mouseX,mouseY, slashing ,timeAcumulator,Cam);

        for(vector <Enemy>::iterator it=Enemies.begin();it!= Enemies.end();)
            {
                if (it->HP<=0||abs(it->chunkNumber-player0.chunkNumber)>1)
                        {
                            if(it->HP<=0)
                            enemiesKilled++;
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
        }


        //updateRightMap when enter new right map
        if(int(player0.position.x/screenWidth)>player0.chunkNumber)
            {player0.chunkNumber++;
                swap(centerMap,leftMap);
                swap(centerChunk,leftChunk);
                swap(centerMap,rightMap);
                swap(centerChunk,rightChunk);
    inputMap(rightMap,basePath+to_string(rand()%numberOfMaps)+".txt");
        loadChunk(rightMap,greenBrick,platform,rightChunk,1,player0.chunkNumber);
                        //spawn Enemy when enter new right map
                         for(int y=1;y<mapTileHeight-1;y++)
                            for(int x=1;x<mapTileWidth-1;x++)
                            {
                                if(rightMap[y][x]!=0
                                   &&rightMap[y-1][x-1]==0&&rightMap[y-1][x]==0&&rightMap[y-1][x+1]==0)
                                if(rand()%100<= spawnRate*100)
                                {
                                    vector2f newEnemyPosition;
                                    newEnemyPosition.x=x*tileSize+(player0.chunkNumber+1)*screenWidth;
                                    newEnemyPosition.y=y*tileSize-entityScalar*enemyHeight;
                                    Enemies.push_back(Enemy(newEnemyPosition,enemyWidth,enemyHeight,enemy));
                                    if(x+7<mapTileWidth) x+=7;
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
                inputMap(leftMap,basePath+to_string(rand()%numberOfMaps)+".txt");
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

        distanceTravelled=max(distanceTravelled,int(player0.position.x-playerStartPosition.x) );
        currentScore=distanceTravelled/distancePerScore+enemiesKilled*scorePerEnemy;

        if(slashing.active) window.RenderTexture(slashing,Cam);


        window.renderText( ("HP: "+to_string(player0.HP)).c_str(),HPPosition);
        window.renderText( ("FPS: "+to_string(currentFPS)).c_str(),FPSPosition);
        window.renderText( ("Score: "+to_string(currentScore)).c_str(),scorePosition);
        window.renderText( ("Highscore: "+to_string(highScore)).c_str(),highScorePosition);


        window.renderCursor(mouseX,mouseY);
        window.Display();

        if(player0.HP<=0) {
                highScore=max(highScore,currentScore);
                ofstream file("res/highscore.txt");
               if(file)
               {
                   file<<highScore;
               }
                file.close();
                gameRunning=0;break;}
    }

    if(endScreen)
    {window.renderText( ("Score: "+to_string(currentScore)).c_str(),scorePosition);
    window.renderText( ("Highscore: "+to_string(highScore)).c_str(),highScorePosition);
    window.renderText("Game over.",vector2f{380,280});
    window.renderText("Press SPACE to replay or ESC to exit the game",vector2f{200,320});
    window.Display();
    }

    while(endScreen)
    {

         while(SDL_PollEvent(&event))
        {
            if(event.type==SDL_QUIT)
                {endScreen=0;
                 goto EndGame;
                }

            if(event.type==SDL_KEYDOWN)
            {
                if(event.key.keysym.sym==SDLK_ESCAPE)
                    goto EndGame;
                if(event.key.keysym.sym==SDLK_SPACE)
                goto GameStart;
            }
        }

    }



    EndGame:

    window.CleanUp();

    return 0;
}
