#ifndef CONSTANTS_HPP_INCLUDED
#define CONSTANTS_HPP_INCLUDED
#include "math.hpp"

const int screenWidth=960;
const int screenHeight=640;
const int mapTileWidth=30;
const int mapTileHeight=20;
const float timeStep= 0.1f;
const int MoveUp=0;
const int MoveDown=1;
const int MoveLeft=2;
const int MoveRight=3;
const int groundLevel=384;
const float MoveSpeed=4.0f;
const float gravity=0.9f;
const float JumpForce=-13.0f;
const float jumpTimer=0.3f;
const int AnimationFramePerSecond=12;
const int FPS=60;
const int playerWidth = 24;
const int playerHeight = 24;
const int slashWidth = 48;
const int slashHeight = 24;
const float slashTimer = 0.3f;
const int tileSize=32;
const float entityScalar = 2.5f;
#define timeStep 0.1f

#endif // CONSTANTS_HPP_INCLUDED
