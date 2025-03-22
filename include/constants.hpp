#ifndef CONSTANTS_HPP_INCLUDED
#define CONSTANTS_HPP_INCLUDED
#include "math.hpp"
#include <string>
#include<SDL.h>
#include<SDL_mixer.h>
using namespace std;
//render constants
const int maxFPS=60;
const float frameDelay=1000.0f/maxFPS;
const float entityScalar = 2.0f;
const int screenWidth=960;
const int screenHeight=640;
const int tileSize=32;
const int mapTileWidth=screenWidth/tileSize;
const int mapTileHeight=screenHeight/tileSize;
const int numberOfMaps=19;
const int textSize=24;
const float timeStep= 0.1f;
const int solidTile=1;
const int platformer=2;
const int mapNumber=4;
const vector2f playerStartPosition={1000,500};
const vector2f HPPosition={750,0};
const vector2f scorePosition={750,24};
const vector2f highScorePosition={750,48};
const vector2f FPSPosition={750,72};
const SDL_Color textcolor={255,50,50,255};
const SDL_Color chosenColor={255,255,255,255};
const int distancePerScore=50;
const int scorePerEnemy=50;
const string basePath="res/mapList/map";
//player movement constants
const float MoveSpeed=5.0f;
const float dashSpeed=15.0f;
const float gravity=0.7f;
const float JumpForce=-10.0f;
const float jumpTimer=0.3f;
const float dashTimer=0.2f;
const float dashCooldown=1.0f;

const float immunityTime=0.2f;
const float slashTimer = 0.8f;
const float slashFallSpeed=3.0f;

//size constant
const int playerWidth = 24;
const int playerHeight = 24;
const int slashWidth = 48;
const int slashHeight = 24;
const int enemyHeight = 24;
const int enemyWidth = 24;
const int wallWidth=105;
const int wallHeight=screenHeight/2;


//enemy constant
const int playerHP=10;
const int enemyHP=3;
const float enemyPushY=-5;
const float enemyPushX=6;
const float enemyDetectRange=7.0f;
const float enemyPatrolSpeed=2.0f;
const float enemyFollowAcceleration=0.1f;
const float attackRange=88;
const float attackAngle=60;
const float spawnRate=0.1f;
const int voidDame=2;
const int wallDame=4;
const int wall=0;
const int ground=1;
const int fly=2;
//music const
const int musicVolume=8;
const int SFXVolume=64;

#endif // CONSTANTS_HPP_INCLUDED
