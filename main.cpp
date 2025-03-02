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
using namespace std;

int mapTile[mapTileHeight][mapTileWidth]=
{
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ,
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ,
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ,
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ,
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ,
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ,
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ,
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ,
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ,
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ,
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ,
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ,
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ,
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0} ,
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0} ,
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0} ,
{1,0,0,0,0,2,2,2,2,2,2,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1} ,
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ,
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ,
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} };


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
    RenderWindow window("Game 1",screenWidth,screenHeight);
    SDL_Texture* testTexture=window.LoadTexture("res/graphics/playerSprite/player24.png");
    SDL_Texture* slashTexture=window.LoadTexture("res/graphics/playerSprite/slash - Copy.png");


    Player player0(vector2f(0,100),testTexture);
    Projectile slashing(vector2f(0,0),slashTexture);

    camera Cam;


    SDL_Texture* greenBrick=window.LoadTexture("res/graphics/tileMap/solidTile.png");
    SDL_Texture* platform=window.LoadTexture("res/graphics/tileMap/platform.png");
    vector <tileMap> brick;
    int res=0;
    for(int y=0;y<20;y++)
        for(int x=0;x<30;x++)
    {
        if(mapTile[y][x]==solidTile) {
            brick.push_back(tileMap(greenBrick,vector2f(32*x,32*y),solidTile));
        }
        else if(mapTile[y][x]==platformer)
        {
            brick.push_back(tileMap(platform,vector2f(32*x,32*y),platformer));
        }
    }
    cout<<brick.size();
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



        player0.checkTileCollision(mapTile);


        slashing.updateProj(timeAcumulator);

        Cam.updateCamera(player0);



        window.ClearScreen();
        for(int i=0;i<brick.size();i++)
        {
            window.RenderMap(brick[i],Cam);
        }
        window.RenderTexture(player0,Cam);
        if(slashing.active) window.RenderTexture(slashing,Cam);
        window.Display();
        SDL_Delay(1000/FPS);
    }




    window.CleanUp();

    return 0;
}
