#include "definitions.h"

static struct player{
  int                 level;
  int                 health;
  int                 experience;
  struct position     pos;
} usr;

void updatePlayerPosition(int direction) {
  switch(direction) {
  case UP:
    --usr.pos.y;
    break;
  case DOWN:
    ++usr.pos.y;
    break;
  case LEFT:
    --usr.pos.x;
    break;
  case RIGHT:
    ++usr.pos.x;
    break;
  default:
    break;
  }
}

void CreatePlayer (int x, int y){
  usr.level = 1;
  usr.health = 100;
  usr.experience = 0;
  usr.pos.x = x;
  usr.pos.y = y;
};


