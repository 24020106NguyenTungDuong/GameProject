#ifndef ENTITY_HPP
#define ENTITY_HPP
#include<SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "utils.hpp"
#include "math.hpp"
#include "animation.hpp"
#include "constants.hpp"
class Entity
{
public:
    Entity(vector2f p_position,SDL_Texture* p_texture);
    SDL_Rect getCurrentFrame();
    SDL_Texture* getTexture();
    vector2f& getPosition(){
    return position;
    }
    void Move();
    bool checkCollision(const SDL_Rect& dstTile);
    void checkTileCollision(int p_mapTile[][mapTileWidth]);
    void handleColision(const SDL_Rect& dstTile,int tileType);
    bool isOnPlatform(const SDL_Rect& dstTile);
    float rightSide();
    float botSide();

public:
int chunkNumber=0;
vector2f position;
vector2f velocity;
bool isAirborne=0;
SDL_Rect currentFrame;
int frameCounter;
int animationRow;
float rotateAngle;
SDL_Point rotateCenter;
SDL_RendererFlip  spriteFlip;
private:
    SDL_Texture* texture;
};
#endif // ENTITY_HPP
