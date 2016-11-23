#define charx
#define chary //character position
#define charHealth 
bool shooting = false;

struct monster{
  int x,y;
};

struct shot{
  int x,y;
};

struct monster enemy = {x,y}; //initialize position of monster


static void aiMove(struct monster, int charx ,int chary){
    int randomizer = rand(); //randomly check if the enemy approaches in x or y
    if(randomizer % 2 == 0){
        if(charx > enemy.x) enemy.x ++ 1;
        else enemy.x -= 1;
    }
    else{
        if(chary > enemy.y) enemy.y += 1;
        else enemy.y -= 1;
    }
    
}

static void aiShoot(){
    shooting = true; //so the enemy only shoots one projectile at a time
    struct shot pew = {enemy.x, enemy.y);
    int travel = 0;
    if(shooting == true;){ //i'm not sure if this is the most efficient way
        if(charx == pew.x && chary > pew.y){
        OrbitOledMoveTo(pew.x, pew.y+1);
        OrbitOledDrawChar('*');
        pew.y ++;
        travel ++;
        }
        if(charx == pew.x && chary < pew.y){
        OrbitOledMoveTo(pew.x, pew.y-1);
        OrbitOledDrawChar('*');
        pew.y --;
        travel ++;
        }
        if(chary == pew.y && charx < pew.x){
        OrbitOledMoveTo(pew.x-1, pew.y);
        OrbitOledDrawChar('*');
        pew.x--;
        travel ++;
        }
        if(chary == pew.y && charx > pew.x){
        OrbitOledMoveTo(pew.x+1, pew.y);
        OrbitOledDrawChar('*');
        pew.x++;
        travel ++;
        }
    }
    if(travel == 5) shooting = false; // limits range of shots
    if(pew.y == charx && pew.y == chary) { //impact
      shooting = false;
      charHealth -= 1;
    }
}

