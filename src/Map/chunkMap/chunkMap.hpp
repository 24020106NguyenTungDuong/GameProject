#ifndef CHUNKMAP_HPP
#define CHUNKMAP_HPP
#include<fstream>
#include<vector>
#include "tileMap.hpp"
#include "constants.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
using namespace std;
//chunk's relative position to player
const int inLeft=-1;
const int inCenter=0;
const int inRight=1;
//2d map arrays that contain tiles type and position
static int leftMap[mapTileHeight][mapTileWidth];
static int centerMap[mapTileHeight][mapTileWidth];
static int rightMap[mapTileHeight][mapTileWidth];

//chunk vectors that contain all tile
static vector <tileMap> leftChunk;
static vector <tileMap> centerChunk;
static vector <tileMap> rightChunk;
//load map array from file
void inputMap(int p_map[][mapTileWidth],string filePath);
//load chunk vector from map array
void loadChunk(int p_map[][mapTileWidth],SDL_Texture* greenBrick,SDL_Texture* platform,vector <tileMap> &chunk,int chunkPosition,int chunkNumber);


#endif // CHUNKMAP_HPP
