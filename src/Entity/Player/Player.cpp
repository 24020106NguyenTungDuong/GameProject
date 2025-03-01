#include "Player.hpp"
#include "constants.hpp"
#include "utils.hpp"

void Player::updatePlayer(const Uint8* keystates,SDL_Event &event, Uint32 &mouseState,Projectile &p_projectile, float timeAcumulator)
{
    velocity.x=0;
    if(velocity.y==0) isAirborne=0;

    if(isAirborne) {velocity.y+=gravity;}

    float currentTime=utils::getTimeSeconds();

    if(keystates[SDL_SCANCODE_A])
    {
        velocity.x=-MoveSpeed;
        spriteFlip=SDL_FLIP_HORIZONTAL;
         currentState=Running;
    }

    if(keystates[SDL_SCANCODE_D])
    {
        velocity.x=MoveSpeed;
        spriteFlip=SDL_FLIP_NONE;
        currentState=Running;
    }

    if(!isAirborne)
        jumpStartTime=currentTime;
    if(keystates[SDL_SCANCODE_SPACE]&&currentTime-jumpStartTime<=jumpTimer)
    {

        currentState=Jumping;
        velocity.y=JumpForce;
         currentState=Jumping;
         isAirborne=1;
    }



    if(velocity.x==0)
        currentState=StandingStill;

    if(velocity.y<0)
        currentState=Jumping;
    else if(velocity.y>0)
        currentState=Falling;



    if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        p_projectile.active=1;
        isSlashing=1;
        p_projectile.spawnTime = currentTime;
    }

           if(spriteFlip==SDL_FLIP_NONE)
        {
            p_projectile.position.x=position.x;
             p_projectile.position.y=position.y+16;
            p_projectile.spriteFlip=spriteFlip;

        }
        else
        {
            p_projectile.position.x=position.x-60;
            p_projectile.position.y=position.y+16;
            p_projectile.spriteFlip=spriteFlip;

        }

    if(currentTime-p_projectile.spawnTime>=0.2f)
        {
            p_projectile.active=0;
            isSlashing=0;
        }

    switch(currentState)
    {
        case StandingStill: animationRow=0;
                            currentFrame.y=animationRow*playerHeight;
                            currentFrame.x = (int(timeAcumulator/timeStep)%6)*playerWidth;
                            break;
        case Running      : animationRow=1;
                            currentFrame.y=animationRow*playerHeight;
                            currentFrame.x = (int(timeAcumulator/timeStep)%6)*playerWidth;
                            break;
        case Jumping      : currentFrame.y=2*playerHeight;
                            currentFrame.x=0;
                            break;
        case Falling      : currentFrame.y=2*playerHeight;
                            currentFrame.x=1*playerWidth;
                            break;

    }

    if(isSlashing)
    {
          switch(currentState)
    {
        case StandingStill: animationRow=3;
                            currentFrame.y=animationRow*playerHeight;
                            currentFrame.x = (int(timeAcumulator/timeStep)%4)*playerWidth;
                            break;
        case Running      : animationRow=4;
                            currentFrame.y=animationRow*playerHeight;
                            currentFrame.x = (int(timeAcumulator/timeStep)%4)*playerWidth;
                            break;
        case Jumping      : animationRow=5;
                            currentFrame.y=animationRow*playerHeight;
                            currentFrame.x = (int(timeAcumulator/timeStep)%4)*playerWidth;
                            break;
        case Falling      : animationRow=5;
                            currentFrame.y=animationRow*playerHeight;
                            currentFrame.x = (int(timeAcumulator/timeStep)%4)*playerWidth;
                            break;

    }

    }
//10 FPS


}

