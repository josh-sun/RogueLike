#include "definitions.h"



struct monster CreateMonster(int level, int x, int y) {
  struct monster enemy;
  enemy.level = level;
  enemy.health = scaleHpWithLevel(level);
  enemy.name = setName();
  enemy.pos.x = x;
  enemy.pos.y = y;
  enemy.isDead = false;
  enemy.damage = scaleDamageWithLevel(level);
  enemy.spDamage = scaleSpDamageWithLevel(level);

  return enemy;
}

static char setAttacks(struct attack *attacks) {

}

static char *setName() {
  int choice = rand()%(4)+1;
  switch (choice) {
  case 1:
    return "Hitler";
  case 2:  
    return "Kim Jung Un";
  case 3:
    return "Osama Bin Laden";
  case 4:
    return "Trump";
  case 5:
    return "Putin God Emperor";
  default:
    return "Putin";
  }
}

static int scaleDamageWithLevel(int level) {
  return level*25;
}

static int scaleSpDamageWithLevel(int level) {
  return level*50+rand()%20;
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

