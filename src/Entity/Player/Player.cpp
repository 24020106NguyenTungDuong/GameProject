#include "Player.hpp"
#include "constants.hpp"
#include "utils.hpp"

void Player::updatePlayer(const Uint8* keystates,SDL_Event &event,const Uint32 &mouseState,int mouseX,int mouseY,Projectile &slashProjectile,Projectile &bulletProjectile, float timeAcumulator,camera Cam,const PlaySound &allSound)
{
    //caculate distance from player to cursor
    SDL_Rect dst;
	dst.x=position.x-Cam.viewPortion.x;
	dst.y=position.y-Cam.viewPortion.y;
	dst.w=currentFrame.w * entityScalar;
	dst.h=currentFrame.h * entityScalar;
    float dx = mouseX - screenWidth/2;
    float dy = mouseY - centerEntity().y;
    vector2f toMouseVector=vector2f(dx,dy);
    toMouseVector.normalise();


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

    //skip all movement when in immunedame state
    if(currentState==ImmuneDame) goto Movement;


    if(!(keystates[SDL_SCANCODE_A]||keystates[SDL_SCANCODE_D]))
        velocity.x=0;









    //start to dash
   if((mouseState & SDL_BUTTON(SDL_BUTTON_RIGHT))&&!isDashing&&!isDashCooldown)
   {
    isDashing=1;
    currentState=Dashing;
    dashStartTime=currentTime;
    velocity={0,0};
            playSound(allSound.dashSound,SFXVolume);
   }





    //handle dash direction
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

            slashProjectile.active=1;
            isSlashing=1;
            slashProjectile.spawnTime = currentTime;
            velocity=toMouseVector*dashSpeed;
            rotateAngle=atan2(dy,dx)*180.0f/M_PI;
            spriteFlip=SDL_FLIP_NONE;
            goto Movement;
       }

   }

    //handle dash cooldown
   if(isDashCooldown&&currentTime-dashCooldownTime>dashCooldown)
   {
       isDashCooldown=0;
   }

   //handle horizontal movement
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


    //handle jump and jump cooldown
    if(!isAirborne)
        jumpStartTime=currentTime;
    if( ( keystates[SDL_SCANCODE_SPACE] ||keystates[SDL_SCANCODE_UP] || keystates[SDL_SCANCODE_W] )&&currentTime-jumpStartTime<=jumpTimer)
    {

        currentState=Jumping;
        velocity.y=JumpForce;
         isAirborne=1;
    }


    //reduce velocity when slashing mid air
    if(isAirborne&&isSlashing&&velocity.y>0)
    velocity.y=slashFallSpeed;
    if(isSlashing&&isAirborne) velocity.x/=2;


    //teleport play to top of screen when fall in the void
    if(position.y>screenHeight-entityScalar*playerHeight/2-tileSize)
    {
            position.y=entityScalar*playerHeight/2;
            velocity.y=1;
            HP-=voidDame;
    }

    //update current state based on velocity
    if(velocity.x==0)
            currentState=StandingStill;
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
    //handle slash attack
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
    slashProjectile.currentFrame.x=int(timeAcumulator/(timeStep/2))%6*slashWidth;
    if(slashProjectile.rotateAngle<-90||slashProjectile.rotateAngle>90)
    slashProjectile.spriteFlip=SDL_FLIP_VERTICAL;
    else slashProjectile.spriteFlip=SDL_FLIP_NONE;

    }



    if(currentTime-slashProjectile.spawnTime>=slashTimer)
    {
            slashProjectile.active=0;
            isSlashing=0;
    }


    //handle bullet attack
    if(!isBulletCooldown)
        shootStartTime=currentTime;

       if( ( keystates[SDL_SCANCODE_S] || keystates[SDL_SCANCODE_DOWN] ) && ammo && !isBulletCooldown)
   {
        isBulletCooldown=1;
        bulletProjectile.active=1;
        bulletProjectile.position=position;
        bulletProjectile.velocity=toMouseVector*bulletSpeed;
        bulletProjectile.rotateCenter={entityScalar*currentFrame.w/2,entityScalar*currentFrame.h/2};
        bulletProjectile.rotateAngle=atan2(dy,dx)*180.0/M_PI;
        if(bulletProjectile.rotateAngle<-90||bulletProjectile.rotateAngle>90)
        bulletProjectile.spriteFlip=SDL_FLIP_VERTICAL;
        else bulletProjectile.spriteFlip=SDL_FLIP_NONE;
        ammo--;
        playSound(allSound.bulletSound,SFXVolume);
   }

   if(isBulletCooldown&&currentTime-shootStartTime>=bulletCooldown)
    {
        isBulletCooldown=0;
    }
   if(distance(bulletProjectile.position,position)>=2*screenWidth)
        bulletProjectile.active=0;


   if(bulletProjectile.active)
   {
       bulletProjectile.currentFrame.x=int(timeAcumulator/(timeStep/2))%8*bulletWidth;
       bulletProjectile.Move();
   }


   //handle animation based on current state
    switch(currentState)
    {
        case StandingStill: animationRow=0;
                            currentFrame.y=animationRow*playerHeight;
                            currentFrame.x = (int(timeAcumulator/timeStep)%6)*playerWidth;
                            break;
        case Running      : animationRow=1;
                            currentFrame.y=animationRow*playerHeight;
                            currentFrame.x = (int(timeAcumulator/timeStep)%6)*playerWidth;

                                   if(!isBulletCooldown&&!isSlashing) playSound(allSound.runningSound,SFXVolume);
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
//Animation is rendered at 10 FPS


}

