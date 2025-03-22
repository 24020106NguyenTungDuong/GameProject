#include "Player.hpp"
#include "constants.hpp"
#include "utils.hpp"

void Player::updatePlayer(const Uint8* keystates,SDL_Event &event,const Uint32 &mouseState,int mouseX,int mouseY,Projectile &slashProjectile, float timeAcumulator,camera Cam,const PlaySound &allSound)
{

    SDL_Rect dst;
	dst.x=position.x-Cam.viewPortion.x;
	dst.y=position.y-Cam.viewPortion.y;
	dst.w=currentFrame.w * entityScalar;
	dst.h=currentFrame.h * entityScalar;
    float dx = mouseX - screenWidth/2;
    float dy = mouseY - centerEntity().y;
    vector2f dashVector=vector2f(dx,dy);
    dashVector.normalise();
    float currentTime=utils::getTimeSeconds();


       if(currentState!=ImmuneDame)
   {
       immunityStartTime=currentTime;
   }
   else if(currentTime-immunityStartTime>immunityTime)
   {
       currentState=StandingStill;
       velocity.x=0;
   }


    if(currentState==ImmuneDame) goto Movement;


    if(!(keystates[SDL_SCANCODE_A]||keystates[SDL_SCANCODE_D]))
        velocity.x=0;



    if(isAirborne&&isSlashing&&velocity.y>0)
    velocity.y=slashFallSpeed;








   if((mouseState & SDL_BUTTON(SDL_BUTTON_RIGHT))&&!isDashing&&!isDashCooldown)
   {
    currentState=Dashing;
    isDashing=1;
    slashProjectile.active=1;
    isSlashing=1;
    slashProjectile.spawnTime = currentTime;
    dashStartTime=currentTime;
    velocity={0,0};
    rotateAngle=atan2(dy,dx)*180.0f/M_PI;
    spriteFlip=SDL_FLIP_NONE;

            playSound(allSound.dashSound,SFXVolume);
   }





   if(isDashing)
   {
       if(currentTime-dashStartTime>dashTimer)
       {
           isDashing=0;
           isSlashing=0;
           slashProjectile.active=0;
           isDashCooldown=1;
           dashCooldownTime=currentTime;
           velocity={0,0};
           rotateAngle=0;
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

    if(keystates[SDL_SCANCODE_A] || keystates[SDL_SCANCODE_LEFT])
    {
        velocity.x=-MoveSpeed;
         currentState=Running;
    }

    if(keystates[SDL_SCANCODE_D] || keystates[SDL_SCANCODE_RIGHT])
    {
        velocity.x=MoveSpeed;
        currentState=Running;
    }



    if(!isAirborne)
        jumpStartTime=currentTime;
    if( ( keystates[SDL_SCANCODE_SPACE] ||keystates[SDL_SCANCODE_UP] || keystates[SDL_SCANCODE_W] )&&currentTime-jumpStartTime<=jumpTimer)
    {

        currentState=Jumping;
        velocity.y=JumpForce;
         isAirborne=1;
    }



    if(isSlashing&&isAirborne) velocity.x/=2;

    if(velocity.x==0)
        currentState=StandingStill;

        if(position.y>screenHeight-entityScalar*playerHeight/2)
        {
            position.y=entityScalar*playerHeight/2;
            velocity.y=1;
            HP-=voidDame;
        }


        if(velocity.y<0)
        currentState=Jumping;
    else if(velocity.y>0)
        currentState=Falling;




    if(velocity.x>=0)
    {
        spriteFlip=SDL_FLIP_NONE;
    }
    else spriteFlip=SDL_FLIP_HORIZONTAL;

Movement:
    Move();
    if( (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT) )&&!isSlashing)
    {
        slashProjectile.active=1;
        isSlashing=1;
        slashProjectile.spawnTime = currentTime;

            playSound(allSound.slashSound,SFXVolume);
    }

    if(isSlashing)
    {
        slashProjectile.position=position;
        slashProjectile.rotateCenter={entityScalar*currentFrame.w/2,entityScalar*currentFrame.h/2};

    slashProjectile.rotateAngle=atan2(dy,dx)*180.0/M_PI;
    if(slashProjectile.rotateAngle<-90||slashProjectile.rotateAngle>90)
    slashProjectile.spriteFlip=SDL_FLIP_VERTICAL;
    else slashProjectile.spriteFlip=SDL_FLIP_NONE;
    }



    if(currentTime-slashProjectile.spawnTime>=slashTimer)
        {
            slashProjectile.active=0;
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

                                        playSound(allSound.runningSound,SFXVolume);
                            break;
        case Jumping      : currentFrame.y=2*playerHeight;
                            currentFrame.x=0;
                            break;
        case Falling      : currentFrame.y=2*playerHeight;
                            currentFrame.x=1*playerWidth;
                            break;
        case Dashing      : currentFrame.y=2*playerHeight;
                            currentFrame.x=(3+int((currentTime-dashStartTime)/dashTimer*3))*playerWidth;

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

