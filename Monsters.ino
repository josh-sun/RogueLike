struct position{
  int x,y;
};

struct monster{
  struct position;
  int health;
  int monsterLevel;
};

struct monster CreateMonster(int x, int y, int level, int health){
  struct monster enemy = {x, y, health, level};  //is x and y going to struct position??
  return enemy;
}

static void UpdateMonsterPosition( struct monster *enemy  ){
  int randomizer = rand(); //randomly decide if the enemy approaches in x or y
    if(randomizer % 2 == 0){
        if(charx > enemy.x) enemy.x ++ 1;
        else enemy.x -= 1;
    }
    else{
        if(chary > enemy.y) enemy.y += 1;
        else enemy.y -= 1;
    }   
}

struct position ReturnPosition (struct monster *enemy){
  return enemy.position;
}


