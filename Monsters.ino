#include "definitions.h"




struct monster CreateMonster(int level, int x, int y) {
  struct monster enemy;
  enemy.health = scaleHpWithLevel(level);
  enemy.name = setName();
  enemy.pos.x = x;
  enemy.pos.y = y;
  return enemy;
}

static char setName() {
  int choice = rand()%(4)+1;
  switch (choice) {
  case 1:
    return 'G';
    break;
  case 2:  
    return 'K';
    break;
  case 3:
    return 'O';
    break;
  case 4:
    return 'T';
    break;
  case 5:
    return 'P';
    break;
  default:
    break;
  }
}


static int scaleHpWithLevel(int level) {
  return level*100+rand()%(50);
}

void UpdateMonsterPosition(struct monster *thisMonster, int direction) {
  switch(direction) {
  case UP:
    --thisMonster->pos.y;
    break;
  case DOWN:
    ++thisMonster->pos.y;
    break;
  case LEFT:
    --thisMonster->pos.x;
    break;
  case RIGHT:
    ++thisMonster->pos.x;
    break;
  default:
    break;
  }
}

