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
  int count = 1;
  switch(enemy.monsterLevel){ //not in order of "difficulty" yet
    case 1: switch (count){
      case 1: enemy.x ++;
      count++;
      case 2: enemy.y --;
      count ++;
      case 3: enemy.x --;
      count ++;
      case 4: enemy.y --;
      count ++;
      case 5: enemy.x ++;
      count ++;
      case 6: enemy.x ++;
      count ++;
      case 7: enemy.y ++;
      count ++;
      case 8: enemy.y ++;
      count ++;
      case 9: enemy.x --;
      count ++;
      case 10: enemy.x --;
      count = 0;
    }   
  case 2: switch (count){
    case 1: enemy.x ++;
    count ++;
    case 2: enemy.x ++;
    count ++;
    case 3: enemy.x --;
    count ++;
    case 4: enemy.x --;
    count = 0;
  }
  
  case 3: switch (count){
    case 1: enemy.y --;
    count ++;
    case 2: enemy.x ++;
    count ++;
    case 3: enemy.y ++;
    count ++;
    case 4: enemy.x --;
    count ++;
    case 5: enemy.y --;
    count ++;
    case 6: enemy.x --;
    count ++;
    case 7: enemy.x --;
    count ++;
    case 8: enemy.y ++;
    count = 0;
  }
  case 4: switch(count){
    case 1: enemy.x --;
    count ++;
    case 2: enemy.y --;
    count ++;
    case 3: enemy.y --;
    count ++;
    case 4: enemy.x ++;
    count ++;
    case 5: enemy.y ++;
    count ++;
    case 6: enemy.y ++;
    count = 0;
  }
  
  case 5: switch (count){
    case 1: enemy.x ++;
    count ++;
    case 2: enemy.x ++;
    count ++;
    case 3: enemy.x --;
    count ++;
    case 4: enemy.x ++;
    count ++;
    case 5: enemy.x ++;
    count ++;
    case 6: enemy.x --;
    count ++;
    case 7: enemy.x --;
    count ++;
    case 8: enemy.x ++;
    count ++;
    case 9: enemy.x --;
    count ++;
    case 10: enemy.x --;
    count = 0;
  }
  
        if(charx > enemy.x) enemy.x += 1;
        else enemy.x -= 1;
    }
    else{
        if(chary > enemy.y) enemy.y += 1;
        else enemy.y -= 1;
    }   
    /* Different ways of enemies moving possible by level
    if(charx > enemy.x) {
      enemy.x += 2;
      enemy.y + 1;
    }
    else {
      enemy.x -= 2;
      enemy.y --;
    }
    /////
    if (charx > enemy.x $$ chary > enemy.y){
      enemy.x ++;
      enemy.y ++;
    }
    else if(char x > enemy.x && chary < enemy.y){
      enemy.x ++;
      enemy.y --;
    }
    */
    
}

struct position ReturnPosition (struct monster *enemy){
  return enemy.position;
}


