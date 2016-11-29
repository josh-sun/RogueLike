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

static char *setName() {
  int choice = rand()%(5)+1;
  Serial.println(choice);
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
    return "Putin";
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

void roam(struct room *thisRoom, struct monster *thisMonster) {
  int direction = rand()%(4);
  UpdateMonsterPosition(thisMonster, direction);
  int x = thisMonster->pos.x;
  int y = thisMonster->pos.y;
  if (((x==thisRoom->pos[0].x || x==thisRoom->pos[1].x) &&
      (y >= thisRoom->pos[0].y && y <= thisRoom->pos[1].y)) ||
      ((y==thisRoom->pos[0].y || y==thisRoom->pos[1].y) &&
      (x >= thisRoom->pos[0].x && x <= thisRoom->pos[1].x))) {
      if (direction==UP) direction = DOWN;
      else if (direction==DOWN) direction = UP;
      else if (direction==LEFT) direction = RIGHT;
      else direction = LEFT;
      UpdateMonsterPosition(thisMonster, direction);
      UpdateMonsterPosition(thisMonster, direction);
      UpdateMonsterPosition(thisMonster, direction);
  }
}

void follow(struct player usr, struct monster *thisMonster, struct room *thisRoom) {
  int direction;
  if (usr.pos.x > thisMonster->pos.x)
    direction = RIGHT;
  else if (usr.pos.x < thisMonster->pos.x)
    direction = LEFT;
  else if (usr.pos.y > thisMonster->pos.y)
    direction = DOWN;
  else 
    direction = UP;
  UpdateMonsterPosition(thisMonster, direction);
  int x = thisMonster->pos.x;
  int y = thisMonster->pos.y;
  if (((x==thisRoom->pos[0].x || x==thisRoom->pos[1].x) &&
      (y >= thisRoom->pos[0].y && y <= thisRoom->pos[1].y)) ||
      ((y==thisRoom->pos[0].y || y==thisRoom->pos[1].y) &&
      (x >= thisRoom->pos[0].x && x <= thisRoom->pos[1].x))) {
      if (direction==UP) direction = DOWN;
      else if (direction==DOWN) direction = UP;
      else if (direction==LEFT) direction = RIGHT;
      else direction = LEFT;
      UpdateMonsterPosition(thisMonster, direction);
  }
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

