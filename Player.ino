#include "definitions.h"

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

struct player CreatePlayer (int x, int y){
  struct player usr;
  usr.level = 1;
  usr.health = 100;
  usr.experience = 0;
  usr.pos.x = x;
  usr.pos.y = y;
  return usr;
};


