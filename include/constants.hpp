#ifndef CONSTANTS_HPP_INCLUDED
#define CONSTANTS_HPP_INCLUDED
#include "math.hpp"
#include <string>
using namespace std;
//render constants
const int FPS=60;
const float entityScalar = 2.0f;
const int screenWidth=960;
const int screenHeight=640;
const int tileSize=32;
const int mapTileWidth=screenWidth/tileSize;
const int mapTileHeight=screenHeight/tileSize;
const int numberOfMaps=5;
const float timeStep= 0.1f;
const int solidTile=1;
const int platformer=2;
const int mapNumber=4;
const string basePath="res/mapList/";
//player movement constants
const float MoveSpeed=6.0f;
const float dashSpeed=15.0f;
const float gravity=0.7f;
const float JumpForce=-10.0f;
const float jumpTimer=0.2f;
const float dashTimer=0.2f;
const float dashCooldown=1.0f;

const float immunityTime=0.3f;
const float slashTimer = 1.0f;
const float slashFallSpeed=3.0f;

//size constant
const int playerWidth = 24;
const int playerHeight = 24;
const int slashWidth = 48;
const int slashHeight = 24;
const int enemyHeight = 24;
const int enemyWidth = 24;



//enemy constant
const int playerHP=10;
const int enemyHP=3;
const float enemyPushY=-5;
const float enemyPushX=10;
const float enemyDetectRange=7.0f;
const float enemyPatrolSpeed=2.0f;
const float enemyFollowAcceleration=0.1f;
const float attackRange=88;
const float attackAngle=60;
const float spawnRate=0.3f;
#define timeStep 0.1f

#endif // CONSTANTS_HPP_INCLUDED
