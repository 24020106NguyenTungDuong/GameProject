#ifndef CONSTANTS_HPP_INCLUDED
#define CONSTANTS_HPP_INCLUDED
#include "math.hpp"
#include <string>
using namespace std;
const int screenWidth=960;
const int screenHeight=640;
const int mapTileWidth=30;
const int mapTileHeight=20;
const int groundLevel=608;
const float timeStep= 0.1f;
const int solidTile=1;
const int platformer=2;
const int mapNumber=4;
const string basePath="res/mapList/";
const float MoveSpeed=6.0f;
const float dashSpeed=15.0f;
const float gravity=0.7f;
const float JumpForce=-10.0f;
const float jumpTimer=0.2f;
const float dashTimer=0.2f;
const float dashCooldown=1.0f;
const int AnimationFramePerSecond=12;
const int FPS=60;
const int playerWidth = 24;
const int playerHeight = 24;
const int slashWidth = 48;
const int slashHeight = 24;
const float slashTimer = 1.0f;
const float slashFallSpeed=3.0f;
const int tileSize=32;
const float entityScalar = 2.0f;
#define timeStep 0.1f

#endif // CONSTANTS_HPP_INCLUDED
