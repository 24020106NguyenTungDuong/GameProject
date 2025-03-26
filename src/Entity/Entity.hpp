#ifndef ENTITY_HPP
#define ENTITY_HPP
#include<SDL.h>
#include <SDL_image.h>
#include<SDL_mixer.h>
#include <iostream>
#include "utils.hpp"
#include "math.hpp"
#include "PlaySound.hpp"
#include "constants.hpp"
class Entity
{
public:
    Entity(vector2f p_position,int entityWidth,int entityHeight,SDL_Texture* p_texture);
    SDL_Rect getCurrentFrame();
    SDL_Texture* getTexture();
    vector2f& getPosition(){
    return position;
    }
    void Move();
    bool checkCollision(const SDL_Rect& dstTile);
    bool checkEntityCollision(Entity p_entity);
    bool isOnPlatform(int p_mapTile[][mapTileWidth]);
    bool canPassThroughPlatform=0;
    void checkTileCollision(int p_mapTile[][mapTileWidth]);
    void handleColision(const SDL_Rect& dstTile,int tileType);
    float rightSide();
    float botSide();
    vector2f centerEntity();

public:
int chunkNumber=0;
vector2f position;
vector2f velocity=vector2f{0,0};
bool isAirborne=0;
SDL_Rect currentFrame;
int frameCounter;
int animationRow;
float rotateAngle;
SDL_Point rotateCenter;
SDL_RendererFlip  spriteFlip;
int HP;
float immunityStartTime;
private:
    SDL_Texture* texture;
};
#endif // ENTITY_HPP
