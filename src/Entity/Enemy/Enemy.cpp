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

    if(enemyType==ground)
    {
                if(distance(position,p_player.position)<=enemyDetectRange*tileSize)
                    isFollowing=1;
                     else isFollowing=0;

                    if(isFollowing)
                {
                    if(abs(velocity.x)<=enemyPatrolSpeed) {velocity.x=enemyPatrolSpeed*sign(p_player.position.x-position.x);}
                    if(p_player.position.x>position.x)
                    velocity.x+=enemyFollowAcceleration;
                else if(p_player.position.x<position.x) velocity.x-=enemyFollowAcceleration;

                  currentFrame.x = (int(timeAcumulator/timeStep)%3+8)*enemyWidth;
                }
                else
                {
                    if(int(currentTime/2)%2) velocity.x=enemyPatrolSpeed;
                    else velocity.x=-enemyPatrolSpeed;
                    currentFrame.x = (int(timeAcumulator/timeStep)%8)*enemyWidth;
                }

    }
    else if(enemyType==fly)
    {
          if(distance(position,p_player.position)<=2*enemyDetectRange*tileSize)
                    isFollowing=1;
                     else isFollowing=0;

        if(isFollowing)
        {
            velocity.x=0.5f*MoveSpeed*sign(p_player.position.x-position.x);
            velocity.y=0.5f*MoveSpeed*sign(p_player.position.y-position.y);
            currentFrame.x=(int(timeAcumulator/timeStep)%3+13)*enemyWidth;

        }
        else
        {
             if(int(currentTime/2)%2) velocity.x=enemyPatrolSpeed;
                    else velocity.x=-enemyPatrolSpeed;
             if(int(currentTime/2)%2) velocity.y=enemyPatrolSpeed;
                    else velocity.y=-1.5f*enemyPatrolSpeed;
                currentFrame.x=(int(timeAcumulator/timeStep)%10)*enemyWidth;

        }


    }
    else
    {
        currentFrame.x=(int(timeAcumulator/timeStep)%8)*enemyWidth;
        return;
    }


    Movement:
        chunkNumber=position.x/screenWidth;
        if(immuneDame)
            currentFrame.y=enemyHeight;
        else currentFrame.y=0;
        if(enemyType==ground)
            velocity.y=0;
     if(velocity.x<0) spriteFlip=SDL_FLIP_HORIZONTAL;
    else spriteFlip=SDL_FLIP_NONE;
    Move();


}
void Enemy::collisionMap(Player p_player,int leftMap[][mapTileWidth],int centerMap[][mapTileWidth],int rightMap[][mapTileWidth])
{
    if(chunkNumber==p_player.chunkNumber)
        {checkTileCollision(centerMap);
        if(enemyType==ground&&!isOnPlatform(centerMap))
        {
            position.x=position.x-velocity.x;
            velocity.x=0;
        }
        }
        else if(chunkNumber>p_player.chunkNumber)
        {checkTileCollision(rightMap);

                if(enemyType==ground&&!isOnPlatform(rightMap))
        {
            position.x=position.x-velocity.x;
            velocity.x=0;
        }
        }
        else
        {checkTileCollision(leftMap);

                if(enemyType==ground&&!isOnPlatform(leftMap))
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
void Enemy::collisionPlayer(Player &p_player,Projectile p_slash,Projectile p_bullet)
{
    if(enemyType==heal)
    {
        if(checkEntityCollision(p_player))
        {
            p_player.HP=min(playerHP,p_player.HP+1);
            HP=0;
        }
        return;
    }
    if(enemyType==ammo)
    {
        if(checkEntityCollision(p_player))
        {
            p_player.ammo=min(p_player.ammo+1,ammoCount);
            HP=0;
        }
        return;
    }
    if(p_bullet.active&&checkEntityCollision(p_bullet))
        HP=0;

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
        velocity=velocity*(-1);
        }
    }




}
void Enemy::updateWall(Player &p_player,float timeAccumulator,camera Cam)
{
    velocity.x=0.3f*MoveSpeed;
    Move();
    position.x=max(float(Cam.viewPortion.x-50),position.x);
    if(p_player.position.x<position.x+wallWidth)
    {
        p_player.velocity.x=2*MoveSpeed;
        p_player.velocity.y=2*JumpForce;
        p_player.HP-=wallDame;
        p_player.currentState=ImmuneDame;
    }
    currentFrame.x=int(timeAccumulator/timeStep)%3*wallWidth;




}
void spawnEnemies(Player player,SDL_Texture* groundType,SDL_Texture* flyType,SDL_Texture* healItem,SDL_Texture* ammoItem,int rightMap[][mapTileWidth],vector <Enemy>& Enemies)
{
                        for(int y=1;y<mapTileHeight;y++)
                            for(int x=1;x<mapTileWidth-1;x++)
                            {
                                if(rightMap[y][x]!=0
                                   &&rightMap[y-1][x-1]==0&&rightMap[y-1][x]==0&&rightMap[y-1][x+1]==0)
                                {


                                          if(rand()%100<=healItemSpawnRate*100)
                                        {
                                            vector2f newEnemyPosition;
                                            newEnemyPosition.x=x*tileSize+(player.chunkNumber+1)*screenWidth;
                                            newEnemyPosition.y=y*tileSize-entityScalar*enemyHeight;
                                            Enemies.push_back(Enemy(newEnemyPosition,enemyWidth,enemyHeight,healItem,heal));
                                        }
                                        if(rand()%100>=100-ammoItemSpawnRate*100)
                                        {
                                            vector2f newEnemyPosition;
                                            newEnemyPosition.x=x*tileSize+(player.chunkNumber+1)*screenWidth;
                                            newEnemyPosition.y=y*tileSize-entityScalar*enemyHeight;
                                            Enemies.push_back(Enemy(newEnemyPosition,enemyWidth,enemyHeight,ammoItem,ammo));
                                        }

                                        if(rand()%100<=spawnRate*100)
                                        {
                                            vector2f newEnemyPosition;
                                            newEnemyPosition.x=x*tileSize+(player.chunkNumber+1)*screenWidth;
                                            newEnemyPosition.y=y*tileSize-entityScalar*enemyHeight;
                                            Enemies.push_back(Enemy(newEnemyPosition,enemyWidth,enemyHeight,groundType,ground));
                                            if(x+7<mapTileWidth) x+=7;
                                            else break;
                                        }

                                }

                                if(rightMap[y-1][x-1]==0&&rightMap[y-1][x]==0&&rightMap[y-1][x+1]==0
                                &&rightMap[y][x-1]==0&&rightMap[y][x]==0&&rightMap[y][x+1]==0
                                &&rightMap[y+1][x-1]==0&&rightMap[y+1][x]==0&&rightMap[y+1][x+1]==0)
                                {
                                    if(rand()%1000<2)
                                    {
                                        vector2f newEnemyPosition;
                                    newEnemyPosition.x=x*tileSize+(player.chunkNumber+1)*screenWidth;
                                    newEnemyPosition.y=y*tileSize-entityScalar*enemyHeight;
                                    Enemies.push_back(Enemy(newEnemyPosition,enemyWidth,enemyHeight,flyType,fly));
                                    }
                                }
                            }
}
void deleteInvalidEnemis(Player player,int& enemiesKilled,vector <Enemy>& Enemies)
{
            for(vector <Enemy>::iterator it=Enemies.begin();it!= Enemies.end();)
            {
                if (it->HP<=0||abs(it->chunkNumber-player.chunkNumber)>1)
                        {
                            if(it->HP<=0)
                            enemiesKilled++;
                            it=Enemies.erase(it);
                        }
                        else
                        {
                            ++it;
                        }
            }


}
