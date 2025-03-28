#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <SDL.h>
#include<cmath>
#include "Entity.hpp"
#include "math.h"
#include "constants.hpp"
#include "camera.hpp"
#include "Projectile.hpp"




enum PlayerState { StandingStill, Running, Jumping, Falling ,Dashing, ImmuneDame};
class Player: public Entity
{
    public:

    Player(vector2f p_position,int entityWidth,int entityHeight,SDL_Texture* p_texture)
    :Entity(p_position,entityWidth,entityHeight,p_texture){HP=playerHP;};
    bool isDashing=0;
    bool isSlashing=0;
    bool isDashCooldown=0;
    bool hasPlayedRunningSound=0;
    bool ammo=1;
    PlayerState currentState=StandingStill;
    void updatePlayer(const Uint8* keystates,SDL_Event &event,const Uint32 &mouseState,int mouseX,int mouseY, Projectile &slashProjectile,Projectile &bulletProjectile , float timeAcumulator,camera Cam,const PlaySound &allSound);
    void updateProjectile(Projectile &p_projectile,Uint32 &mouseState);

    private:
     float jumpStartTime;
    float dashStartTime;
    float dashCooldownTime;


};
//Mix_Chunk* slashSound = Mix_LoadWAV("res/SFX/slash.wav");

#endif // PLAYER_HPP
