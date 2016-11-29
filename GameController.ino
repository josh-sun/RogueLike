#include <stdbool.h>
#include <string.h>
#include "definitions.h"
#include <FillPat.h>
#include <LaunchPad.h>
#include <OrbitBoosterPackDefs.h>
#include <OrbitOled.h>
#include <OrbitOledChar.h>
#include <OrbitOledGrph.h>



//Forward Declarations
struct player CreatePlayer (int x, int y);
struct monster CreateMonster(int level, int x, int y);
struct levelMap CreateLevel(int level);
void updatePlayerPosition(struct player *usr, int direction);

struct ButtonState { 
  bool state;
  bool isRising;
};

static struct InputState {
  bool                switches[2];
  struct ButtonState  buttons[2];
  int                 tiltDirection;
  float               potentiometer;
} gameInputState;

static struct gameState {
  int                 level;
  struct levelMap     curr_level;
  struct player       usr;
} ActiveGame;

static struct fightState {
  struct monster      *enemy;
  int                 dodgeDirection;
  bool                playerDodged;
  bool                playerWin;
  bool                enemyWin;
  int                 enemyAttackType;
} FightStatus;

static enum FightScenes {
  Encounter,
  DrawMonster,
  EnemyAttack,
  EnemyAttackResult,
  PlayerAttack,
  PlayerAttackResult,
  BattleResult,
} CurrentFightScene = Encounter;


static enum GameMenu {
  Welcome,
  Game,
  Fight,
} gameCurrentPage = Welcome;

static void printCurrentStatus() {
  Serial.println("Current Game Status");
  Serial.println("*Player*: ");
  Serial.print("Level: ");
  Serial.println(ActiveGame.usr.level);
  Serial.print("Health: ");
  Serial.println(ActiveGame.usr.health);
  Serial.print("Experience: ");
  Serial.println(ActiveGame.usr.experience);
  Serial.print("Damage: ");
  Serial.println(ActiveGame.usr.damage);
  Serial.println("*Monster*: ");
  Serial.print("Level: ");
  Serial.println(FightStatus.enemy->level);
  Serial.print("Name: ");
  Serial.println(FightStatus.enemy->name);
  Serial.print("Health: ");
  Serial.println(FightStatus.enemy->health);
  Serial.print("Damage: ");
  Serial.println(FightStatus.enemy->damage);
  Serial.println("");
}

static char *intToCharArray(char buf[], int num) {
  String numStr = String(num);
  numStr.toCharArray(buf,4);
  return buf;
}

static void handleFightScene(int scene){
  switch (scene) {
    case Encounter:
      FightStatus.dodgeDirection = NO_TILT;
      FightStatus.playerWin = false;
      FightStatus.enemyWin = false;
      OrbitOledClearBuffer();
      OrbitOledMoveTo(0,2);
      OrbitOledDrawString("A Wild ");
      OrbitOledMoveTo(0,12);
      OrbitOledDrawString(FightStatus.enemy->name);
      OrbitOledMoveTo(0,22);
      OrbitOledDrawString("Has Appeared!");
      if (gameInputState.buttons[0].isRising) {
        CurrentFightScene = FightScenes((int)CurrentFightScene+1);
      }
      break;
    case DrawMonster:
      OrbitOledClearBuffer();
    
      OrbitOledMoveTo(45,5);    //head
      OrbitOledDrawRect(83,25); 
      OrbitOledMoveTo(46,6);
      OrbitOledDrawRect(82,24);
      
      OrbitOledMoveTo(45,2);    //ears
      OrbitOledLineTo(45,5);
      OrbitOledMoveTo(45,2);
      OrbitOledLineTo(52,5);
    
      OrbitOledMoveTo(83,2);
      OrbitOledLineTo(83,5);
      OrbitOledMoveTo(83,2);
      OrbitOledLineTo(76,5);
    
      OrbitOledMoveTo(59,12);   //eyes
      OrbitOledDrawRect(55,16);
      OrbitOledMoveTo(69,12);
      OrbitOledDrawRect(73,16);
    
      OrbitOledMoveTo(64,17);   //mouth
      OrbitOledLineTo(59,23);
      OrbitOledMoveTo(64,17);
      OrbitOledLineTo(69,23);
    
      OrbitOledMoveTo(55,8);    //eyebrows
      OrbitOledLineTo(61,12);
      OrbitOledMoveTo(73,8);
      OrbitOledLineTo(67,12);
    
      OrbitOledMoveTo(34,32);   //arms
      OrbitOledLineTo(28,17);
      OrbitOledMoveTo(37,32);
      OrbitOledLineTo(31,17);
      OrbitOledMoveTo(91,32);
      OrbitOledLineTo(97,17);
      OrbitOledMoveTo(94,32);
      OrbitOledLineTo(100,17);
    
      OrbitOledMoveTo(28,17);
      OrbitOledLineTo(22,11);
      OrbitOledMoveTo(22,11);
      OrbitOledLineTo(28,13);
      OrbitOledMoveTo(28,13);
      OrbitOledLineTo(27,6);
      OrbitOledMoveTo(27,6);
      OrbitOledLineTo(29,11);
      OrbitOledMoveTo(29,11);
      OrbitOledLineTo(31,8);
      OrbitOledMoveTo(31,8);
      OrbitOledLineTo(31,17);
    
      OrbitOledMoveTo(100,17);
      OrbitOledLineTo(106,11);
      OrbitOledMoveTo(106,11);
      OrbitOledLineTo(100,13);
      OrbitOledMoveTo(100,13);
      OrbitOledLineTo(101,6);
      OrbitOledMoveTo(101,6);
      OrbitOledLineTo(99,11);
      OrbitOledMoveTo(99,11);
      OrbitOledLineTo(97,8);
      OrbitOledMoveTo(97,8);
      OrbitOledMoveTo(97,17);
      if (gameInputState.buttons[0].isRising) {
        CurrentFightScene = FightScenes((int)CurrentFightScene+1);
      }
      break;
    case EnemyAttack:
    {
      OrbitOledClearBuffer();
      OrbitOledMoveTo(0,0);
      OrbitOledDrawString(FightStatus.enemy->name);
      OrbitOledMoveTo(0,12);
      FightStatus.enemyAttackType = rand();
      if (FightStatus.enemyAttackType ==0)
        OrbitOledDrawString(FightStatus.enemy->attacks.basicAttack);
      else {
        int specialAttackType = rand()%3;
        OrbitOledDrawString(FightStatus.enemy->attacks.spAttacks[specialAttackType]);
      }
      OrbitOledUpdate();
      delay(1500);
      OrbitOledClearBuffer();
      OrbitOledMoveTo(0,0);
      OrbitOledDrawString("Dodge ");
      FightStatus.dodgeDirection = rand()%(3);
      switch (FightStatus.dodgeDirection) {
      case UP:
        OrbitOledDrawString("Up NOW!");
        break;
      case DOWN:
        OrbitOledDrawString("Down NOW!");
        break;
      case LEFT:
        OrbitOledDrawString("Left NOW!");
        break;
      case RIGHT:
        OrbitOledDrawString("Right NOW!");
        break;   
      default:
        break;
      }
      OrbitOledUpdate();
      int t1 = millis();
      while (millis()-t1<1000) {
        double xyz[3];
        gameInputState.tiltDirection = CalcTiltDirection(ReadAccelG(xyz));
      }
      if (gameInputState.tiltDirection == FightStatus.dodgeDirection)
        FightStatus.playerDodged = true;
      else {
        FightStatus.playerDodged = false;
        if (FightStatus.enemyAttackType == 0)
          ActiveGame.usr.health-=FightStatus.enemy->damage;
        else
          ActiveGame.usr.health-=FightStatus.enemy->spDamage;
      }
      CurrentFightScene = FightScenes((int)CurrentFightScene+1);
    }
    case EnemyAttackResult:
    {
      OrbitOledClearBuffer();
      if (FightStatus.playerDodged) {
        OrbitOledMoveTo(0,2);
        OrbitOledDrawString("Player Dodged");
        OrbitOledMoveTo(0,12);
        OrbitOledDrawString("Monster's Attack!");
        printCurrentStatus();
      } else {
        OrbitOledMoveTo(0,2);
        OrbitOledDrawString("Player Was Hit!");
        OrbitOledMoveTo(0,12);
        OrbitOledDrawString("Damage Done: ");
        OrbitOledMoveTo(0,22);
        char buf[4];
        if (FightStatus.enemyAttackType == 0)
          OrbitOledDrawString(intToCharArray(buf, FightStatus.enemy->damage));
        else 
          OrbitOledDrawString(intToCharArray(buf, FightStatus.enemy->spDamage));
      }
      if (gameInputState.buttons[0].isRising && ActiveGame.usr.health > 0) {
        printCurrentStatus();
        CurrentFightScene = FightScenes((int)CurrentFightScene+1);
      }
      break;
    }
    case PlayerAttack:
    {
      OrbitOledClearBuffer();
      OrbitOledMoveTo(0,2);
      OrbitOledDrawString("Your Turn:");
      OrbitOledMoveTo(0,12);
      OrbitOledDrawString("Shake to Attack!");
      double xyz[3];
      
      if (isShaking(ReadAccelG(xyz))) {
        CurrentFightScene = FightScenes((int)CurrentFightScene+1);
        FightStatus.enemy->health-=ActiveGame.usr.damage;
      }
      
      break;
    }
    case PlayerAttackResult:
    {
      OrbitOledClearBuffer();
      OrbitOledMoveTo(0,2);
      OrbitOledDrawString("Monster Was Hit!");
      OrbitOledMoveTo(0,12);
      OrbitOledDrawString("Damage Done: ");
      OrbitOledMoveTo(0,22);
      char buf[4];
      OrbitOledDrawString(intToCharArray(buf, ActiveGame.usr.damage));
      if (gameInputState.buttons[0].isRising && FightStatus.enemy->health > 0) {
        printCurrentStatus();
        CurrentFightScene = FightScenes((int)CurrentFightScene-3);
      }
      break;
    }
    case BattleResult:
    {
     if (FightStatus.playerWin) {
      FightStatus.enemy->isDead = true;
      OrbitOledClearBuffer();
      OrbitOledMoveTo(0,2);
      OrbitOledDrawString("The Monster Has");
      OrbitOledMoveTo(0,12);
      OrbitOledDrawString("Been Slain!");
      if (gameInputState.buttons[0].isRising) {
        gameCurrentPage = Game;
      }
     }
     if (FightStatus.enemyWin) {
      OrbitOledClearBuffer();
      OrbitOledMoveTo(0,2);
      OrbitOledDrawString("The Player Has");
      OrbitOledMoveTo(0,12);
      OrbitOledDrawString("Lost the Game!");
      OrbitOledMoveTo(0,22);
      OrbitOledDrawString("RIP");
      if (gameInputState.buttons[0].isRising) {
        gameCurrentPage = Welcome;
      }
     }
     break;
    }
  }
  if (ActiveGame.usr.health <= 0) {
    FightStatus.enemyWin = true;
    CurrentFightScene = BattleResult;
  }
  if (FightStatus.enemy->health <= 0) {
    FightStatus.playerWin = true;
    CurrentFightScene = BattleResult;
  }
}

static bool roomOverlapsWithScreen (struct position pos[], int x1, int y1, int x2, int y2) {
if (pos[0].x > x2 || x1 > pos[1].x ||
    pos[0].y > y2 || y1 > pos[1].y) 
      return false;  
  return true;
}

static void handleInput() {
  int ux = ActiveGame.usr.pos.x;
  int uy = ActiveGame.usr.pos.y;

  int surroundings[3][3] = {0};
  struct monster *surroundingMonsters[3][3];
  
  for (int x = ux-1; x <= ux+1; x++) {
    for (int y = uy-1; y <= uy+1; y++) {
      
      //if map border 
      if (x<=0 || y<=0 || x >=ActiveGame.curr_level.len || y >= ActiveGame.curr_level.wid) {
        surroundings[y-uy+1][x-ux+1] = 1;
        continue;
      }

      //check room borders and monster positions
      for (int i = 0; i < ActiveGame.curr_level.roomCount; i++) {
        
        //monsters
        if (!ActiveGame.curr_level.monsters[i].isDead && x==ActiveGame.curr_level.monsters[i].pos.x && y==ActiveGame.curr_level.monsters[i].pos.y) {
          surroundings[y-uy+1][x-ux+1] = 2;
          surroundingMonsters[y-uy+1][x-ux+1] = &ActiveGame.curr_level.monsters[i];
          break;
        }

        //horizontal and vertical room walls
        if (((x==ActiveGame.curr_level.rooms[i].pos[0].x || x==ActiveGame.curr_level.rooms[i].pos[1].x) &&
            (y >= ActiveGame.curr_level.rooms[i].pos[0].y && y <= ActiveGame.curr_level.rooms[i].pos[1].y)) ||
            ((y==ActiveGame.curr_level.rooms[i].pos[0].y || y==ActiveGame.curr_level.rooms[i].pos[1].y) &&
            (x >= ActiveGame.curr_level.rooms[i].pos[0].x && x <= ActiveGame.curr_level.rooms[i].pos[1].x))) {
            surroundings[y-ActiveGame.usr.pos.y+1][x-ActiveGame.usr.pos.x+1] = 1;
            break;
        }

      }
    }
  }
  
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      Serial.print(surroundings[i][j]);
      Serial.print(" ");
    }
    Serial.println("");
  }
  Serial.println("");
  
  switch (gameInputState.tiltDirection) {
    case UP:
      if(surroundings[0][1]==0)
        updatePlayerPosition(&ActiveGame.usr, gameInputState.tiltDirection);
      else if (surroundings[0][1]==2) {
        FightStatus.enemy = surroundingMonsters[0][1];
        gameCurrentPage = Fight;
      }
      break;
    case DOWN:
      if(surroundings[2][1]==0)
        updatePlayerPosition(&ActiveGame.usr, gameInputState.tiltDirection);
      else if (surroundings[2][1]==2) {
        FightStatus.enemy = surroundingMonsters[2][1];
        gameCurrentPage = Fight;      
      }
      break;   
    case LEFT:
      if(surroundings[1][0]==0)
        updatePlayerPosition(&ActiveGame.usr, gameInputState.tiltDirection);
      else if (surroundings[1][0]==2) {
        FightStatus.enemy = surroundingMonsters[1][0];
        gameCurrentPage = Fight;      
      }
      break;
    case RIGHT:
      if(surroundings[1][2]==0)
        updatePlayerPosition(&ActiveGame.usr, gameInputState.tiltDirection);
      else if (surroundings[1][2]==2) {
        FightStatus.enemy = surroundingMonsters[1][2];
        gameCurrentPage = Fight;      
      }
      break;
    default:
      break;
  }  
}


static void renderView() {
  OrbitOledClearBuffer();

  //screen position on game grid
  int sx1 = ActiveGame.usr.pos.x-8;
  int sy1 = ActiveGame.usr.pos.y-2;
  int sx2 = ActiveGame.usr.pos.x+8;
  int sy2 = ActiveGame.usr.pos.y+1;

  //**************Draw Map Bondaries***************
  if(sx1 < 0 || sy1 < 0 || sx2 > ActiveGame.curr_level.len || sy2 > ActiveGame.curr_level.wid) {
    if (sx1 < 0 || sx2 > ActiveGame.curr_level.len) {
      int x;
      if (sx1 < 0) x = 0;
      else x = ActiveGame.curr_level.len;
      for (int y = 1; y < ActiveGame.curr_level.wid-1; y++) {
        OrbitOledMoveTo((x-sx1)*CHAR_PIXEL, (y-sy1)*CHAR_PIXEL);
        OrbitOledDrawChar('|');
      }
    }
    if (sy1 < 0 || sy2 > ActiveGame.curr_level.wid) {
        int y;
        if (sy1 < 0) y = 0;
        else y = ActiveGame.curr_level.wid;
        for (int x = 0; x < ActiveGame.curr_level.len; x++) {
          OrbitOledMoveTo((x-sx1)*CHAR_PIXEL, (y-sy1)*CHAR_PIXEL);
          OrbitOledDrawChar('-');
        }
      }
  }

  
  //**************Draw Rooms and Monsters***************
  for (int i = 0; i < ActiveGame.curr_level.roomCount; i++) {
    //room position on game grid
    int rx1 = ActiveGame.curr_level.rooms[i].pos[0].x;
    int ry1 = ActiveGame.curr_level.rooms[i].pos[0].y;
    int rx2 = ActiveGame.curr_level.rooms[i].pos[1].x;
    int ry2 = ActiveGame.curr_level.rooms[i].pos[1].y;

    //monster position on game grid
    int mx, my;
    if (ActiveGame.curr_level.monsters[i].isDead) {
      mx = -999;
      my = -999;
    } else {
      mx = ActiveGame.curr_level.monsters[i].pos.x;
      my = ActiveGame.curr_level.monsters[i].pos.y;
    }

    //If room overlap with view
    if (roomOverlapsWithScreen(
          ActiveGame.curr_level.rooms[i].pos,
          ActiveGame.usr.pos.x-8,
          ActiveGame.usr.pos.y-2,
          ActiveGame.usr.pos.x+8,
          ActiveGame.usr.pos.y+1)) 
    {  
      if (mx >= sx1 && mx <= sx2 &&
          my >= sy1 && my <= sy2)
      {
        OrbitOledMoveTo((mx-sx1)*CHAR_PIXEL, (my-sy1)*CHAR_PIXEL);
        OrbitOledDrawChar(ActiveGame.curr_level.monsters[i].name[0]);
      }
      
      for (int x = rx1; x <= rx2; x++) {
        for (int y = ry1; y <= ry2; y++) {
          if (x >= sx1 && x <=sx2 && y>=sy1 && y<=sy2 && 
             (x!=mx || y!=my)) 
          {
            if ((x==rx1 || x==rx2) && (y!=ry1 && y!=ry2)) 
            {
                OrbitOledMoveTo((x-sx1)*CHAR_PIXEL, (y-sy1)*CHAR_PIXEL);
                OrbitOledDrawChar('|');
            }
            else if (y==ry1 || y==ry2) 
            {
                OrbitOledMoveTo((x-sx1)*CHAR_PIXEL, (y-sy1)*CHAR_PIXEL);
                OrbitOledDrawChar('-');
            }
            else 
            {
              OrbitOledMoveTo((x-sx1)*CHAR_PIXEL, (y-sy1)*CHAR_PIXEL);
              OrbitOledDrawChar('.');
            }
          }
        }
      }
    }
  }

  //**************Draw Player***************
  OrbitOledMoveTo((ActiveGame.usr.pos.x-sx1)*CHAR_PIXEL, (ActiveGame.usr.pos.y-sy1)*CHAR_PIXEL);
  OrbitOledDrawChar('@');
  
}



static void handlePageWelcome(){
  OrbitOledClearBuffer();
  OrbitOledMoveTo(8, 0);
  OrbitOledDrawString("--Dungeon RPG--");
  
  OrbitOledMoveTo(0, 10);
  OrbitOledDrawString("BTN1 - Start");
  
  if(gameInputState.buttons[0].isRising) 
    gameCurrentPage = Game;

}


void PageSelection() {
  
  switch(gameCurrentPage)
  {
  case Welcome:
    handlePageWelcome();
    break;
  case Game:
    renderView();
    handleInput();
    break;
  case Fight:
    handleFightScene(CurrentFightScene);
  default:
    break;
  }
  OrbitOledUpdate();
}

//initialize oled screen
void GameControllerInit() {
  OrbitOledInit();
  OrbitOledClear();
  OrbitOledClearBuffer();
  OrbitOledSetFillPattern(OrbitOledGetStdPattern(iptnSolid));
  OrbitOledSetDrawMode(modOledSet);
  OrbitOledSetCharUpdate(0);
  ActiveGame.curr_level = CreateLevel(1);
  int x, y;
  do {
    x = rand()%(ActiveGame.curr_level.rooms[0].pos[1].x-ActiveGame.curr_level.rooms[0].pos[0].x-2)+ActiveGame.curr_level.rooms[0].pos[0].x+1;
    y = rand()%(ActiveGame.curr_level.rooms[0].pos[1].y-ActiveGame.curr_level.rooms[0].pos[0].y-2)+ActiveGame.curr_level.rooms[0].pos[0].y+1;
  } while (x==ActiveGame.curr_level.monsters[0].pos.x && y==ActiveGame.curr_level.monsters[0].pos.y);
  ActiveGame.usr = CreatePlayer(x,y);
}




