#include <iostream>
#define SDL_MAIN_HANDLED
#include<SDL.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
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
#include "PlaySound.hpp"
#include "chunkMap/chunkMap.hpp"
#include "Enemy.hpp"
using namespace std;
void renderMenu(Uint32 mouseState,int mouseX,int mouseY,RenderWindow &window,bool &inMenu,bool &inHelp,bool &gameOver,bool &gameRunning,SDL_Texture* Menu)
{
                            window.renderPNG(Menu);
            if(mouseX<=170&&mouseX>=100&&mouseY>=520&&mouseY<=544)
            {
                window.renderText("Start",vector2f(100,screenHeight-120));
                if( mouseState & SDL_BUTTON_LEFT) inMenu=0;
            }
            else  window.renderText("Start",vector2f(100,screenHeight-120),chosenColor);

            if(mouseX<=170&&mouseX>=100&&mouseY>=544&&mouseY<=568)
            {
                window.renderText("Help",vector2f(100,screenHeight-96));
                if( mouseState & SDL_BUTTON_LEFT) inHelp=1;
            }
            else window.renderText("Help",vector2f(100,screenHeight-96),chosenColor);

            if(mouseX<=170&&mouseX>=100&&mouseY>=568&&mouseY<=592)
            {
                window.renderText("Exit",vector2f(100,screenHeight-72));
                if( mouseState & SDL_BUTTON_LEFT) {gameOver=0;inMenu=0;gameRunning=0;}
            }
            else  window.renderText("Exit",vector2f(100,screenHeight-72),chosenColor);



            window.renderCursor(mouseX,mouseY);
            window.Display();
}

void renderHelp(Uint32 mouseState,int mouseX,int mouseY,RenderWindow &window,bool &inMenu,bool &inHelp,SDL_Texture* Menu)
{
       window.ClearScreen();

                window.renderPNG(Menu);
                window.renderText("A/D or Left/Right Arrow to move",vector2f(100,100),chosenColor);
                window.renderText("Left click to slash",vector2f(100,124),chosenColor);
                window.renderText("S/Down Arrow to fire a bullet when you have ammo",vector2f(100,148),chosenColor);
                window.renderText("Right click to dash",vector2f(100,172),chosenColor);
                window.renderText("Hold SPACE/Up Arrow to jump high",vector2f(100,196),chosenColor);
                window.renderText("Press SPACE/Up Arrow to jump low",vector2f(100,220),chosenColor);
                window.renderText("When in game press ESC to pause",vector2f(100,244),chosenColor);
                window.renderText("You can damage enemies by slashing, dashing or jumping on them",vector2f(100,268),chosenColor);
                window.renderText("Enjoy!!",vector2f(100,292),chosenColor);

                if(mouseX<=screenWidth/2+40&&mouseX>=screenWidth/2-30&&mouseY>=576&&mouseY<=600)
                {
                    window.renderText("Menu",vector2f(screenWidth/2-30,screenHeight-64));
                    if( mouseState & SDL_BUTTON_LEFT) inHelp=0;
                }
                else  window.renderText("Menu",vector2f(screenWidth/2-30,screenHeight-64),chosenColor);

            window.renderCursor(mouseX,mouseY);
            window.Display();
}
void renderPause(Uint32 mouseState,int mouseX,int mouseY,RenderWindow &window,bool &pause,bool &replay,SDL_Texture* pausecreen)
{
                    window.renderPNG(pausecreen);
                if(mouseX<=450&&mouseX>=380&&mouseY>=320&&mouseY<=344)
                {
                    window.renderText("Resume",vector2f(screenWidth/2-100,screenHeight/2));
                    if( mouseState & SDL_BUTTON_LEFT) pause=0;
                }
                else window.renderText("Resume",vector2f(screenWidth/2-100,screenHeight/2),chosenColor);

                if(mouseX<=450&&mouseX>=380&&mouseY>=344&&mouseY<=368)
                {
                    window.renderText("Restart",vector2f(screenWidth/2-100,screenHeight/2+24));
                    if( mouseState & SDL_BUTTON_LEFT) {pause=0;replay=1;}

                }
                else window.renderText("Restart",vector2f(screenWidth/2-100,screenHeight/2+24),chosenColor);
                window.renderCursor(mouseX,mouseY);
                window.Display();

}
void Cleanup(vector<SDL_Texture*>& textures) {
    for (SDL_Texture*& texture:textures) {
        if (texture!=nullptr) {
            SDL_DestroyTexture(texture);
            texture=nullptr;
        }
    }
}

int main(int argc, char *argv[])
{
    srand(time(0));
    if(SDL_Init(SDL_INIT_VIDEO)!=0||SDL_Init(SDL_INIT_AUDIO)!=0)
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
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
            cout<<"SDL_mixer Init failed: "<<Mix_GetError()<<endl;
            return 1;
        }
    //prepare all game resources
    RenderWindow window("Slash and Dash",screenWidth,screenHeight);
    SDL_Texture* testTexture=window.LoadTexture("res/graphics/playerSprite/player.png");
    SDL_Texture* slashTexture=window.LoadTexture("res/graphics/playerSprite/slash.png");
    SDL_Texture* bulletTexture=window.LoadTexture("res/graphics/playerSprite/bullet.png");
    SDL_Texture* Cursor=window.LoadTexture("res/graphics/playerSprite/cursor.png");
    SDL_Texture* greenBrick=window.LoadTexture("res/graphics/tileMap/solidTile.png");
    SDL_Texture* platform=window.LoadTexture("res/graphics/tileMap/platform.png");
    SDL_Texture* pausecreen=window.LoadTexture("res/graphics/blank.png");
    SDL_Texture* Menu=window.LoadTexture("res/graphics/menu.png");
    SDL_Texture* groundType=window.LoadTexture("res/graphics/EnemySprite/groundType.png");
    SDL_Texture* flyType=window.LoadTexture("res/graphics/EnemySprite/flyType.png");
    SDL_Texture* healItem=window.LoadTexture("res/graphics/ItemSprite/heal.png");
    SDL_Texture* ammoItem=window.LoadTexture("res/graphics/ItemSprite/ammo.png");
    SDL_Texture* wall=window.LoadTexture("res/graphics/Wall/wall.png");

    SDL_ShowCursor(SDL_DISABLE);

    PlaySound allSound;

    TTF_Font* font = TTF_OpenFont("res/font/8bitOperatorPlus-Regular.ttf", 24);

    if (!font) {
        cout <<"Font loading failed:"<<TTF_GetError()<<endl;
        return 1;
    }







    //play background music
    Mix_PlayMusic(allSound.backgroundMusic,-1);
    Mix_VolumeMusic(musicVolume);

    bool inMenu=1;

    // game start flag
    GameStart:

    //maps that have been used in each cycle
    bool usedMap[numberOfMaps+1]={0};
    int numberOfUsedMaps=0;

    //prepare first map
    inputMap(centerMap,basePath+"1.txt");
    inputMap(rightMap,basePath+to_string(rand()%numberOfMaps)+".txt");

    Player player(playerStartPosition,playerWidth,playerHeight,testTexture);
    Projectile slashing(vector2f(0,0),slashWidth,slashHeight,slashTexture);
    Projectile bullet((vector2f(0,0)),bulletWidth,bulletHeight,bulletTexture);
    camera Cam;
    //update player's chunk number
    player.chunkNumber=player.position.x/screenWidth;





    //create tile from 2d map array
    loadChunk(centerMap,greenBrick,platform,centerChunk,inCenter,player.chunkNumber);
    loadChunk(rightMap,greenBrick,platform,rightChunk,inRight,player.chunkNumber);
    loadChunk(leftMap,greenBrick,platform,leftChunk,inLeft,player.chunkNumber);


    //the wall that chases player
    Enemy wallOfFlesh(vector2f(Cam.viewPortion.x,0),wallWidth,wallHeight,wall);

    bool gameRunning=1;
    bool gameOver=1;
    bool pause=0;
    bool replay=0;
    bool inHelp=0;
    int currentScore=0;
    int highScore=0;
    int enemiesKilled=0;
    int distanceTravelled=0;
    float FPSadjust=-3;
    ifstream file("res/highScore.txt");
    if(file)
    {
        file>>highScore;
    }
    file.close();

    SDL_Event event;


    //time management
    float startLoopTime=utils::getTimeSeconds();
    float currentTime=0.0f;
    float timeAcumulator=0.0f;
    float frameTime=0;
    int frameCount=0;
    int currentFPS=60;

    //main gameloop
    while(gameRunning)
    {


        while(SDL_PollEvent(&event))
        {
            if(event.type==SDL_QUIT)
                {
                    gameRunning=0;
                    gameOver=0;
                    break;
                }
                if(event.type==SDL_KEYDOWN&&event.key.keysym.sym==SDLK_ESCAPE)
                {
                    pause=!pause;
                }
                if(pause&&event.type==SDL_KEYDOWN&&event.key.keysym.sym==SDLK_r)
                    goto GameStart;
                if(inMenu&&event.type==SDL_KEYDOWN)
                    switch(event.key.keysym.sym)
                {case SDLK_r:
                    inMenu=0;
                    break;
                case  SDLK_ESCAPE:
                    goto EndGame;
                };

        }
        //get key and mouse state
        const Uint8* keystates=SDL_GetKeyboardState(NULL);
        int mouseX, mouseY;
        Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);


        //get time in each game loop and count the frame
        currentTime=utils::getTimeSeconds();
        frameTime=currentTime-startLoopTime;
        timeAcumulator+=frameTime;
        startLoopTime=currentTime;
        frameCount++;

        //adjust FPS to be around 60
        SDL_Delay(frameDelay+FPSadjust);
        if(timeAcumulator>=1.0f) {
                                    timeAcumulator-=1.0f;
                                    currentFPS=frameCount;
                                    frameCount=0;
                                            if(currentFPS<FPS) FPSadjust-=0.5f;
                                            else if(currentFPS>FPS+FPSrange) FPSadjust+=0.05f;
                                 }

        if(inHelp)
        {
            renderHelp(mouseState,mouseX,mouseY,window,inMenu,inHelp,Menu);
            continue;
        }
        if(inMenu)
        {
            renderMenu(mouseState,mouseX,mouseY,window,inMenu,inHelp,gameOver,gameRunning,Menu);
            continue;
        }
        if(pause==1)
        {
            renderPause(mouseState,mouseX,mouseY,window,pause,replay,pausecreen);
            if(replay) goto GameStart;
            continue;
        }







        //update player's movement and state
        player.updatePlayer(keystates,event, mouseState,mouseX,mouseY, slashing, bullet ,timeAcumulator,Cam,allSound);
        deleteInvalidEnemis(player,enemiesKilled,Enemies);

        //check enemies collision and update their movement, state
          for(int i=0;i<Enemies.size();i++)
        {
            Enemies[i].collisionPlayer(player,slashing,bullet);
            Enemies[i].updateEnemy(player,currentTime,timeAcumulator);
        }


        //updateRightMap when enter new right map
        if(int(player.position.x/screenWidth)>player.chunkNumber)
                {
                player.chunkNumber++;
                swap(centerMap,leftMap);
                swap(centerChunk,leftChunk);
                swap(centerMap,rightMap);
                swap(centerChunk,rightChunk);

                //chose random map that has not appear in this cycle
                           int mapIndex=rand()%numberOfMaps;
                           while(usedMap[mapIndex])
                            mapIndex=rand()%numberOfMaps;
                    numberOfUsedMaps++;
                    if(numberOfUsedMaps==numberOfMaps)
                    {
                        numberOfUsedMaps=0;
                        for(int i=0;i<numberOfMaps;i++)
                            usedMap[i]=0;
                    }
                    usedMap[mapIndex]=1;

        //input map from file to 2d map array
        inputMap(rightMap,basePath+to_string(mapIndex)+".txt");
        loadChunk(rightMap,greenBrick,platform,rightChunk,inRight,player.chunkNumber);


                spawnEnemies(player,groundType,flyType,healItem,ammoItem,rightMap,Enemies);
            }
        //updateLeftMap when enter new left map
         if(int(player.position.x/screenWidth)<player.chunkNumber)
            {
                player.chunkNumber--;
                swap(leftMap,centerMap);
                swap(leftChunk,centerChunk);
                swap(leftMap,rightMap);
                swap(leftChunk,rightChunk);
            }


        //check player collision with tiles
        player.checkTileCollision(centerMap);

        //keep player in screen center
        Cam.updateCamera(player);


        window.ClearScreen();

        window.renderBackGround();
        window.renderChunk(Cam,leftChunk,centerChunk,rightChunk);
        window.RenderTexture(player,Cam);

                for(int i=0;i<Enemies.size();i++)
        {
            Enemies[i].collisionMap(player,leftMap,centerMap,rightMap);
            window.RenderTexture(Enemies[i],Cam);
        }

        wallOfFlesh.updateWall(player,timeAcumulator,Cam);
        window.RenderTexture(wallOfFlesh,Cam);

        distanceTravelled=max(distanceTravelled,int(player.position.x-playerStartPosition.x) );
        currentScore=distanceTravelled/distancePerScore+enemiesKilled*scorePerEnemy;



        if(slashing.active)
        {
            window.RenderTexture(slashing,Cam);
        }
        if(bullet.active)
        {
            window.RenderTexture(bullet,Cam);
        }

        if(player.HP<=0)
                {
                            highScore=max(highScore,currentScore);
                            ofstream file("res/highscore.txt");
                           if(file)
                               {
                                   file<<highScore;
                               }
                            file.close();
                            gameRunning=0;break;
                }


        window.renderText( ("HP: "+to_string(player.HP)).c_str(),HPPosition);
        window.renderText( ("Ammo: "+to_string(player.ammo)).c_str(),ammoPosition);
        window.renderText( ("FPS: "+to_string(currentFPS)).c_str(),FPSPosition);
        window.renderText( ("Score: "+to_string(currentScore)).c_str(),scorePosition);
        window.renderText( ("Highscore: "+to_string(highScore)).c_str(),highScorePosition);
        window.renderCursor(mouseX,mouseY);
        window.Display();


    }

    //game over screen
    if(gameOver)
    {
    window.renderPNG(pausecreen);
    window.renderText( ("Score: "+to_string(currentScore)).c_str(),scorePosition);
    window.renderText( ("Highscore: "+to_string(highScore)).c_str(),highScorePosition);
    window.renderText("Game over.",vector2f{380,280});
    window.renderText("Replay (R)",vector2f{380,320});
    window.renderText("Exit (ESC)",vector2f{380,344});
    window.Display();
    }

    while(gameOver)
    {

         while(SDL_PollEvent(&event))
        {
            if(event.type==SDL_QUIT)
                {
                    gameOver=0;
                    goto EndGame;
                }

            if(event.type==SDL_KEYDOWN)
                {
                    if(event.key.keysym.sym==SDLK_ESCAPE)
                        goto EndGame;
                    if(event.key.keysym.sym==SDLK_r)
                    goto GameStart;
                }
        }
    }


    //free all the resources
    EndGame:

    vector<SDL_Texture*> textures = {
        testTexture, slashTexture, bulletTexture, Cursor, greenBrick, platform, pausecreen,
        Menu, groundType, flyType, healItem, ammoItem, wall
    };
    TTF_CloseFont(font);
    font=nullptr;
    allSound.CleanUp();
    Cleanup(textures);
    window.CleanUp();

    return 0;
}
