#ifndef TILEMAP_HPP
#define TILEMAP_HPP
#include<SDL.h>

#include "math.h"
#include "constants.hpp"

class tileMap
{
    public:
        SDL_Texture* tileSprite;
        vector2f position;
        SDL_Rect src;
        SDL_Rect dst;
        int tileType;
    public:
        tileMap();
        tileMap(SDL_Texture* p_tileSprite,vector2f p_position,int p_tileType)
        :   tileSprite(p_tileSprite),position(p_position),tileType(p_tileType)
        {
            if(tileType==solidTile)
            src.x=rand()%8*16;
            else if(tileType==platformer)
                src.x=rand()%4*16;
            src.y=0;
            src.w=16;
            src.h=16;
            dst.x=position.x;
            dst.y=position.y;
            dst.w=32;
            dst.h=32;

        }
        SDL_Texture* getTexture();
    protected:

    private:
};

#endif // TILEMAP_HPP
