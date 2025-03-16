#include "Entity.hpp"
#include "constants.hpp"
#include<SDL.h>
#include <SDL_image.h>
#include "math.hpp"
using namespace std;
Entity::Entity(vector2f p_position,int entityWidth,int entityHeight,SDL_Texture* p_texture)
    :position(p_position),texture(p_texture)
{
    currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = entityWidth;
	currentFrame.h = entityHeight;
	frameCounter=0;
	animationRow=0;
    rotateAngle=0.0f;
    rotateCenter={entityScalar*currentFrame.w/2,entityScalar*currentFrame.h/2};
    spriteFlip=SDL_FLIP_NONE;
}
void Entity::Move()
{
    if(velocity.y==0) isAirborne=0;
     if(isAirborne) velocity.y+=gravity;
    position=velocity+position;
}
SDL_Texture* Entity::getTexture()
{
    return texture;
}
float Entity::botSide()
{
        return position.y+entityScalar*currentFrame.h;


}
float Entity::rightSide()
{
    return position.x+entityScalar*currentFrame.w;


}
vector2f Entity::centerEntity()
{
    return {position.x+entityScalar*currentFrame.w/2,position.y+entityScalar*currentFrame.h/2};
}
bool Entity::checkCollision(const SDL_Rect& dstTile)
{
      return !(rightSide()<dstTile.x      ||
            position.x>dstTile.x+tileSize ||
            botSide()<=dstTile.y          ||
            position.y>=dstTile.y+tileSize);
}
bool Entity::checkEntityCollision(Entity p_entity)
{
    return !(rightSide()<p_entity.position.x     ||
            position.x>p_entity.rightSide() ||
            botSide()<=p_entity.position.y          ||
            position.y>=p_entity.botSide());
}

void Entity::handleColision(const SDL_Rect& dstTile,int tileType)
{

    //Huong va cham
    float left=rightSide()-dstTile.x;
    float right=(dstTile.x+tileSize)-position.x;
    float bot=dstTile.y+tileSize-position.y;
    float top= botSide()-dstTile.y;


    float minCollision=std::min(std::min(left,right),std::min(bot,top));

    if(tileType==solidTile)
    {

    if(minCollision==left&&velocity.x>0)
    {
        position.x=dstTile.x-entityScalar*currentFrame.w;
        velocity.x=0;
    }
    else if(minCollision==top&&velocity.y>0)
    {
        position.y=dstTile.y-entityScalar*currentFrame.h-1;
        velocity.y=0;
        isAirborne=0;
    }
    else if(minCollision==bot&&velocity.y<0)
    {
        position.y=dstTile.y+tileSize;
       velocity.y=1;
        isAirborne=1;


    }
    else if(minCollision==right&&velocity.x<0)
    {
        position.x=dstTile.x+tileSize;
        velocity.x=0;
    }

    }

    if(tileType==platformer)
    {
        if(minCollision==top&&velocity.y>0)
    {


        position.y=dstTile.y-entityScalar*currentFrame.h-1;
        velocity.y=0;
        isAirborne=0;

    }

    }




}
bool Entity::isOnPlatform(int p_mapTile[][mapTileWidth])
{
        int entityLeft=(position.x)/tileSize;
    int entityCenter=(position.x+entityScalar*currentFrame.w/2)/tileSize;
    int entityRight=(rightSide())/tileSize;
     int botTile=(botSide()+1)/tileSize;
    entityRight=entityRight%30;
    entityCenter=entityCenter%30;
    entityLeft=entityLeft%30;




    if(p_mapTile[botTile][entityRight]||p_mapTile[botTile][entityCenter]||p_mapTile[botTile][entityLeft]) return 1;

    return 0;
}
void Entity::checkTileCollision(int p_mapTile[][mapTileWidth])
{

    int leftTile=(position.x-1)/tileSize;
    int rightTile=(rightSide()+1)/tileSize;
    int topTile=(position.y-1)/tileSize;
    int botTile=(botSide()+1)/tileSize;

        rightTile=rightTile%30;
        leftTile=leftTile%30;

    if(!isAirborne&&!isOnPlatform(p_mapTile)) {
        isAirborne=1;
        velocity.y=1;
    }


        for (int y = topTile; y <= botTile; y++)
         {
                 for (int x = leftTile; x <= rightTile; x++)

                        {
                                if(p_mapTile[y][x])
                            {
                            SDL_Rect dstTile={
                            tileSize*x+chunkNumber*screenWidth,
                            tileSize*y,
                            tileSize,
                            tileSize,
                            };
                            if(checkCollision(dstTile))
                                {

                                        handleColision(dstTile,p_mapTile[y][x]);


                                }
                            }

                        }
        }



}
