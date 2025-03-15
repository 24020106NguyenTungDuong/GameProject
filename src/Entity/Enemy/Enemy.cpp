#include "Enemy.hpp"

void Enemy::updateEnemy(Player p_player,float currentTime,float timeAcumulator)
{

    if(abs(p_player.position.x-position.x)<15*tileSize&&abs(p_player.position.y-position.y)<5*tileSize)
        isFollowing=1;
    else isFollowing=0;
    if(isFollowing)
    {if(p_player.position.x>position.x)
        velocity.x+=0.03f*MoveSpeed;
    else if(p_player.position.x<position.x) velocity.x-=0.03f*MoveSpeed;
    //if(p_player.currentState!=Dashing&&p_player.isAirborne) velocity.y=0.7f*p_player.velocity.y;

      if(distance(p_player.position,position)<5) velocity={0,0};
      currentFrame.x = (int(timeAcumulator/timeStep)%3+8)*playerWidth;
    }
    else
    {
        if(int(currentTime/2)%2) velocity.x=0.7*MoveSpeed;
        else velocity.x=-0.7f*MoveSpeed;
        currentFrame.x = (int(timeAcumulator/timeStep)%8)*playerWidth;
    }
    chunkNumber=position.x/screenWidth;
    if(velocity.x<0) spriteFlip=SDL_FLIP_HORIZONTAL;
    else spriteFlip=SDL_FLIP_NONE;

    velocity.y=0;
    Move();


}
void Enemy::keepOnPlatForm(Player p_player,int leftMap[][mapTileWidth],int centerMap[][mapTileWidth],int rightMap[][mapTileWidth])
{
    if(chunkNumber==p_player.chunkNumber)
        {checkTileCollision(centerMap);
        if(!isOnPlatform(centerMap))
        {
            position.x=position.x-velocity.x;
            velocity.x=0;
        }
        }
        else if(chunkNumber>p_player.chunkNumber)
        {checkTileCollision(rightMap);

                if(!isOnPlatform(rightMap))
        {
            position.x=position.x-velocity.x;
            velocity.x=0;
        }
        }
        else
        {checkTileCollision(leftMap);

                if(!isOnPlatform(leftMap))
        {
            position.x=position.x-velocity.x;
            velocity.x=0;
        }
        }


}
