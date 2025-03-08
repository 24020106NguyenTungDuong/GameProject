#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <SDL.h>
#include<cmath>
#include "Entity.hpp"
#include "math.h"
#include "constants.hpp"
#include "camera.hpp"
#include "Projectile.hpp"


enum PlayerState { StandingStill, Running, Jumping, Falling ,Dashing};
class Player: public Entity
{
    public:

    Player(vector2f p_position,SDL_Texture* p_texture)
    :Entity(p_position,p_texture){}
    bool isDashing=0;
    bool isSlashing=0;
    bool isDashCooldown=0;
    float dashCooldownTime;
    PlayerState currentState=StandingStill;
    void updatePlayer(const Uint8* keystates,SDL_Event &event,const Uint32 &mouseState,int mouseX,int mouseY, Projectile &p_projectile , float timeAcumulator,camera Cam);
    void updateProjectile(Projectile &p_projectile,Uint32 &mouseState);
     float jumpStartTime;
    float dashStartTime;
    private:
};

#endif // PLAYER_HPP
