#include "Enemy.hpp"

void Enemy::updateEnemy(Player p_player,float currentTime,float timeAcumulator)
{
      if(!immuneDame)
   {
       immunityStartTime=currentTime;
   }
   else if(currentTime-immunityStartTime>immunityTime)
   {
       immuneDame=0;
   }
   if(immuneDame)  goto Movement;
    if(distance(position,p_player.position)<=enemyDetectRange*tileSize)
        isFollowing=1;
    else isFollowing=0;
    if(isFollowing)
    {
        if(abs(velocity.x)<=enemyPatrolSpeed) {velocity.x=enemyPatrolSpeed*sign(p_player.position.x-position.x);}
        if(p_player.position.x>position.x)
        velocity.x+=enemyFollowAcceleration;
    else if(p_player.position.x<position.x) velocity.x-=enemyFollowAcceleration;

      //if(distance(p_player.position,position)<5) velocity={0,0};
      currentFrame.x = (int(timeAcumulator/timeStep)%3+8)*playerWidth;
    }
    else
    {
        if(int(currentTime/2)%2) velocity.x=enemyPatrolSpeed;
        else velocity.x=-enemyPatrolSpeed;
        currentFrame.x = (int(timeAcumulator/timeStep)%8)*playerWidth;
    }
    chunkNumber=position.x/screenWidth;
    if(velocity.x<0) spriteFlip=SDL_FLIP_HORIZONTAL;
    else spriteFlip=SDL_FLIP_NONE;

    Movement:
        if(immuneDame)
            currentFrame.y=enemyHeight;
        else currentFrame.y=0;
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
bool Enemy::checkSlashCollision(Player p_player,Projectile p_slash)
{
    vector2f dxdy=centerEntity()+(p_player.centerEntity()*(-1));
    float distanceToEnemy=distance(centerEntity(),p_player.centerEntity());
    if(distanceToEnemy>attackRange) return 0;
    float angleToEnemy=atan2(dxdy.y,dxdy.x)*180.0f/M_PI;
    float angleDiff=angleToEnemy-p_slash.rotateAngle;
    if(angleDiff>180) angleDiff-=360;
    else if(angleDiff<=-180) angleDiff+=360;
    if(abs(angleDiff)>attackAngle/2) return 0;
    return 1;
}
void Enemy::collisionPlayer(Player &p_player,Projectile p_slash)
{

      if(p_player.isSlashing&&checkSlashCollision(p_player,p_slash))
    {
            velocity.x=2.0f*MoveSpeed*sign(position.x-p_player.position.x);
            HP--;
            immuneDame=1;
    }
    if(checkEntityCollision(p_player)&&p_player.currentState==Falling )
    {
         velocity.x=0;
            HP--;
            immuneDame=1;
        p_player.velocity.y=JumpForce;
    }


    if(!immuneDame)
    {
    if(checkEntityCollision(p_player)&&p_player.currentState==Dashing)
        {
        HP=0;
        return;
        }
    if(checkEntityCollision(p_player)&&p_player.currentState!=ImmuneDame)
        {
        p_player.velocity.x=enemyPushX*sign(velocity.x);
        p_player.velocity.y=enemyPushY;
        p_player.isAirborne=1;
        p_player.currentState=ImmuneDame;
        p_player.HP--;
        velocity.x=-velocity.x;
        }
    }




}
void Enemy::updateWall(Player &p_player,float timeAccumulator,camera Cam)
{
    velocity.x=0.1f*MoveSpeed;
    Move();
    position.x=max(float(Cam.viewPortion.x-50),position.x);
    if(p_player.position.x<position.x+wallWidth*entityScalar)
    {
        p_player.velocity.x=2*MoveSpeed;
        p_player.velocity.y=2*JumpForce;
        p_player.HP--;
        p_player.currentState=ImmuneDame;
    }
    currentFrame.x=int(timeAccumulator/timeStep)%7*wallWidth;




}
