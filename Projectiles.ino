#include "definitions.h"

struct projectile {
  struct position   pos;
  int               direction; 
  int               damage;
};

struct projectile CreateProjectile(int x, int y, int dir, int dmg){
  struct projectile shot;
  shot.pos.x = x;
  shot.pos.y = y;
  shot.direction = dir;
  shot.damage = dmg;
  return shot;
};

void UpdateProjectilePosition(struct projectile *shot){
  switch(shot->direction){
    case UP:    
      --shot->pos.y;
      break;
    case DOWN:  
      ++shot->pos.y;
      break;
    case LEFT: 
      --shot->pos.x;
      break;
    case RIGHT: 
      ++shot->pos.x;
      break;
    default:
      break;
   }
}

