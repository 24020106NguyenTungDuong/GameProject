#ifndef ENEMY_HPP
#define ENEMY_HPP
#include<math.h>
#include "Entity.hpp"
#include "Player.hpp"
#include "chunkMap/chunkMap.hpp"
class Enemy: public Entity
{
    public:
    Enemy(vector2f p_position,int entityWidth,int entityHeight,SDL_Texture* p_texture)
    :Entity(p_position,entityWidth,entityHeight,p_texture){};
    bool isAttacking;
    bool isFollowing;
    bool isPatrolling;
    void updateEnemy(Player p_player,float currentTime,float timeAcumulator);
    float patrolStartTime;
    void keepOnPlatForm(Player p_player,int leftMap[][mapTileWidth],int centerMap[][mapTileWidth],int rightMap[][mapTileWidth]);
    void attackPlayer(Player &p_player);
    private:
};

#endif // ENEMY_HPP
