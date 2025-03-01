#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "animation.hpp"
#include "Entity.hpp"
#include "math.h"
#include "constants.hpp"
#include "SDL.h"
#include "Projectile.hpp"


enum PlayerState { StandingStill, Running, Jumping, Falling };
class Player: public Entity
{
    public:

    Player(vector2f p_position,SDL_Texture* p_texture)
    :Entity(p_position,p_texture){}

    bool isSlashing=1;
    PlayerState currentState=StandingStill;
    void updatePlayer(const Uint8* keystates,SDL_Event &event, Uint32 &mouseState, Projectile &p_projectile , float timeAcumulator);
    void updateProjectile(Projectile &p_projectile,Uint32 &mouseState);
    float jumpStartTime;

    private:
};

#endif // PLAYER_HPP
