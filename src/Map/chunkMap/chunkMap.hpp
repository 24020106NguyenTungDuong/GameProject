#ifndef CHUNKMAP_HPP
#define CHUNKMAP_HPP
#include<fstream>
#include<vector>
#include "tileMap.hpp"
#include "constants.hpp"
using namespace std;
const int inLeft=-1;
const int inCenter=0;
const int inRight=1;
static int leftMap[mapTileHeight][mapTileWidth];
static int centerMap[mapTileHeight][mapTileWidth];
static int rightMap[mapTileHeight][mapTileWidth];

static vector <tileMap> leftChunk;
static vector <tileMap> centerChunk;
static vector <tileMap> rightChunk;
void inputMap(int p_map[][mapTileWidth],string filePath);
void loadChunk(int p_map[][mapTileWidth],SDL_Texture* greenBrick,SDL_Texture* platform,vector <tileMap> &chunk,int chunkPosition,int chunkNumber);

#endif // CHUNKMAP_HPP
