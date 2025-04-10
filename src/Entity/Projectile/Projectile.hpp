#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP
#include "Entity.hpp"
#include "math.hpp"
#include "constants.hpp"
class Projectile: public Entity
{
    public:
        Projectile(vector2f p_position,int entityWidth,int entityHeight,SDL_Texture* p_texture)
    :Entity(p_position,entityWidth,entityHeight,p_texture){
        currentFrame.x=0;
        currentFrame.y=0;
        currentFrame.w=entityWidth;
        currentFrame.h=entityHeight;
    };

    public:
        bool active=0;
        float spawnTime;

    private:
};

#endif // PROJECTILE_HPP
