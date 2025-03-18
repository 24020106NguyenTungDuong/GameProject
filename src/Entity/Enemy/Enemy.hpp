#ifndef ENEMY_HPP
#define ENEMY_HPP
#include<math.h>
#include"camera.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "chunkMap/chunkMap.hpp"
enum EnemyType{groundType=3,flyingType=4};
class Enemy: public Entity
{
    public:
    Enemy(vector2f p_position,int entityWidth,int entityHeight,SDL_Texture* p_texture)
    :Entity(p_position,entityWidth,entityHeight,p_texture){HP=enemyHP;
                                                            chunkNumber=position.x/screenWidth;
                                                            immuneDame=0;
                                                            };
    bool immuneDame;
    bool isAttacking;
    bool isFollowing;
    bool isPatrolling;
    void updateEnemy(Player p_player,float currentTime,float timeAcumulator);
    void updateWall(Player &p_player,float timeAccumulator,camera Cam);
    float patrolStartTime;
    void keepOnPlatForm(Player p_player,int leftMap[][mapTileWidth],int centerMap[][mapTileWidth],int rightMap[][mapTileWidth]);
    void collisionPlayer(Player &p_player,Projectile p_slash);
    bool checkSlashCollision(Player p_player,Projectile p_slash);
    private:
};
static vector <Enemy> Enemies;
#endif // ENEMY_HPP
