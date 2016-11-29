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
  struct monster      enemy;
  bool                playerDodged;
  bool                monsterDodged;
} FightStatus;

static enum FightScenes {
  Encounter,
  DrawMonster,
  Battle,
} CurrentFightScene = Encounter;


static enum GameMenu {
  Welcome,
  Game,
  Fight,
} gameCurrentPage = Welcome;

static void handleFightScene(int scene){
  switch (scene) {
    case Encounter:
      OrbitOledClearBuffer();
      OrbitOledMoveTo(5,5);
      OrbitOledDrawString("A wild ");
      OrbitOledDrawString(FightStatus.enemy.name);
      OrbitOledDrawString(" has appeared!");
      break;
    case DrawMonster:
      OrbitOledClearBuffer();
      /* 
      char monster1 [ROOM_HEIGHT][ROOM_WIDTH]= 
      { {'.','.','.','.','.','^','_','_','_','^','.','.','.','.','.','.'},
        {'.','.','.','.','.','|','*',' ','*','|','.','.','.','.','.','.'},
        {'.','.','.','.','.','|',' ','^',' ','|','.','.','.','.','.','.'},
        {'.','.','.','_','_','_','-','-','-','_','_','_','.','.','.','.'}
      }; //working on doing this with pixels instead
      for (int i = 0; i < ROOM_WIDTH; i++ ) {
        for (int j = 0; j < ROOM_HEIGHT; j++) {
          OrbitOledMoveTo(i*CHAR_PIXEL,j*CHAR_PIXEL);
          OrbitOledDrawChar(monster1[j][i]);
        }
      }
      */
      break;
    case Battle:

  
                                
      OrbitOledMoveTo(0,0);
      //attack message
      
    
      /*
      if(thisMonster.level < 2) 
        OrbitOledDrawString("%c", basicAttack);
      else if(thisMonster.level < 6) 
        OrbitOledDrawString("%c", specialAttacks[rand() % 4]);
      else 
        OrbitOledDrawString("%c", abilities[rand() % 2]);
    */
      OrbitOledClearBuffer();
  
      break;
    default:
      break;
  }
  if (gameInputState.buttons[0].isRising) {
    CurrentFightScene = FightScenes((int)CurrentFightScene+1);
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
  struct monster surroundingMonsters[3][3];
  
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
        if (x==ActiveGame.curr_level.monsters[i].pos.x && y==ActiveGame.curr_level.monsters[i].pos.y) {
          surroundings[y-uy+1][x-ux+1] = 2;
          surroundingMonsters[y-uy+1][x-ux+1] = ActiveGame.curr_level.monsters[i];
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
  /*
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      Serial.print(surroundings[i][j]);
      Serial.print(" ");
    }
    Serial.println("");
  }
  Serial.println("");
  */
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
    int mx = ActiveGame.curr_level.monsters[i].pos.x;
    int my = ActiveGame.curr_level.monsters[i].pos.y;

    //If
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




