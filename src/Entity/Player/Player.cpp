#include "Player.hpp"
#include "constants.hpp"
#include "utils.hpp"

void Player::updatePlayer(const Uint8* keystates,SDL_Event &event,const Uint32 &mouseState,int mouseX,int mouseY,Projectile &p_projectile, float timeAcumulator,camera Cam)
{


    if(!(keystates[SDL_SCANCODE_A]||keystates[SDL_SCANCODE_D]||keystates[SDL_SCANCODE_LSHIFT]))
        velocity.x=0;
                SDL_Rect dst;
	dst.x=position.x-Cam.viewPortion.x;
	dst.y=position.y-Cam.viewPortion.y;
	dst.w=currentFrame.w * entityScalar;
	dst.h=currentFrame.h * entityScalar;
    float dx = mouseX - screenWidth/2;
    float dy = mouseY - (position.y+entityScalar*currentFrame.h/2);

//    if(botSide()>groundLevel)
//    {
//        position.y=groundLevel-entityScalar*currentFrame.h-1;
//        isAirborne=0;
//        velocity.y=0;
//    }
    if(velocity.y==0) isAirborne=0;

    if(isAirborne) {velocity.y+=gravity;
    if(isSlashing) velocity.y=slashFallSpeed;
    }

    float currentTime=utils::getTimeSeconds();


     vector2f dashVector=vector2f(dx,dy);
    dashVector.normalise();


   if(keystates[SDL_SCANCODE_LSHIFT]&&!isDashing&&!isDashCooldown)
   {
        currentState=Dashing;
       isDashing=1;
            p_projectile.active=1;
        isSlashing=1;
        p_projectile.spawnTime = currentTime;
       dashStartTime=currentTime;
       velocity={0,0};
   }

   if(isDashing)
   {
       if(currentTime-dashStartTime>dashTimer)
       {
           isDashing=0;
           isDashCooldown=1;
           dashCooldownTime=currentTime;
           velocity={0,0};
       }
       else
       {
           velocity=dashVector*dashSpeed;
           goto Movement;
       }

   }

   if(isDashCooldown&&currentTime-dashCooldownTime>dashCooldown)
   {
       isDashCooldown=0;
   }

    if(keystates[SDL_SCANCODE_A])
    {
        velocity.x=-MoveSpeed;
         currentState=Running;
    }

    if(keystates[SDL_SCANCODE_D])
    {
        velocity.x=MoveSpeed;
        currentState=Running;
    }



    if(!isAirborne)
        jumpStartTime=currentTime;
    if(keystates[SDL_SCANCODE_SPACE]&&currentTime-jumpStartTime<=jumpTimer)
    {

        currentState=Jumping;
        velocity.y=JumpForce;
         isAirborne=1;
    }



    if(isSlashing&&isAirborne) velocity.x/=2;

    if(velocity.x==0)
        currentState=StandingStill;

    if(velocity.y<0)
        currentState=Jumping;
    else if(velocity.y>0)
        currentState=Falling;

Movement:
    Move();

    if(velocity.x>=0)
    {
        spriteFlip=SDL_FLIP_NONE;
    }
    else spriteFlip=SDL_FLIP_HORIZONTAL;


    if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        p_projectile.active=1;
        isSlashing=1;
        p_projectile.spawnTime = currentTime;

    }

    if(isSlashing)
    {
        p_projectile.position=position;
        p_projectile.rotateCenter={entityScalar*currentFrame.w/2,entityScalar*currentFrame.h/2};

    p_projectile.rotateAngle=atan2(dy,dx)*180.0/M_PI;
    if(p_projectile.rotateAngle<-90||p_projectile.rotateAngle>90)
    p_projectile.spriteFlip=SDL_FLIP_VERTICAL;
    else p_projectile.spriteFlip=SDL_FLIP_NONE;
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
        case Dashing      : currentFrame.y=2*playerHeight;
                            currentFrame.x=3*playerWidth;

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

