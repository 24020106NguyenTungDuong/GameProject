#ifndef CHUNKMAP_HPP
#define CHUNKMAP_HPP
#include<fstream>
#include<vector>
#include "tileMap.hpp"
#include "constants.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
using namespace std;
const int inLeft=-1;
const int inCenter=0;
const int inRight=1;
static int leftMap[mapTileHeight][mapTileWidth];
static int centerMap[mapTileHeight][mapTileWidth];
static int rightMap[mapTileHeight][mapTileWidth];

 static string mapList[numberOfMaps]={"res/mapList/map1.txt","res/mapList/map2.txt","res/mapList/map3.txt","res/mapList/map4.txt"};
static vector <tileMap> leftChunk;
static vector <tileMap> centerChunk;
static vector <tileMap> rightChunk;
void inputMap(int p_map[][mapTileWidth],string filePath);
void loadChunk(int p_map[][mapTileWidth],SDL_Texture* greenBrick,SDL_Texture* platform,vector <tileMap> &chunk,int chunkPosition,int chunkNumber);
void updateRightMap(Player p_player,SDL_Texture* greenBrick,SDL_Texture* platform);
#endif // CHUNKMAP_HPP
