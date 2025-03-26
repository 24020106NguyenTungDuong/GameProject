#ifndef ENEMY_HPP
#define ENEMY_HPP
#include<math.h>
#include"camera.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "chunkMap/chunkMap.hpp"
class Enemy: public Entity
{
    public:
    Enemy(vector2f p_position,int entityWidth,int entityHeight,SDL_Texture* p_texture,int type=0)
    :Entity(p_position,entityWidth,entityHeight,p_texture){HP=enemyHP;
                                                            chunkNumber=position.x/screenWidth;
                                                            immuneDame=0;
                                                            enemyType=type;
                                                            };

    void updateEnemy(Player p_player,float currentTime,float timeAcumulator);
    void updateWall(Player &p_player,float timeAccumulator,camera Cam);
    void collisionMap(Player p_player,int leftMap[][mapTileWidth],int centerMap[][mapTileWidth],int rightMap[][mapTileWidth]);
    void collisionPlayer(Player &p_player,Projectile p_slash);
    bool checkSlashCollision(Player p_player,Projectile p_slash);
     int enemyType;
    private:
    bool immuneDame;
    bool isAttacking;
    bool isFollowing;
    bool isPatrolling;
    float patrolStartTime;


};
static vector <Enemy> Enemies;
void spawnEnemies(Player player,SDL_Texture* groundType,SDL_Texture* flyType,int rightMap[][mapTileWidth],vector <Enemy>& Enemies);
void deleteInvalidEnemis(Player player,int& enemiesKilled,vector <Enemy>& Enemies);
#endif // ENEMY_HPP
