#include "definitions.h"

struct player CreatePlayer (int x, int y){
  struct player usr;
  usr.health = 100;
  usr.pos.x = x;
  usr.pos.y = y;
  usr.damage = 100;
  return usr;
};

struct player LevelUpPlayer (struct player usr, int x, int y){
  usr.health += 50;
  usr.pos.x = x;
  usr.pos.y = y;
  usr.damage += 20;
  return usr;
};

void updatePlayerPosition(struct player *usr, int direction) {
  switch(direction) {
  case UP:
    --usr->pos.y;
    break;
  case DOWN:
    ++usr->pos.y;
    break;
  case LEFT:
    --usr->pos.x;
    break;
  case RIGHT:
    ++usr->pos.x;
    break;
  default:
    break;
  }
}




