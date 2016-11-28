#include <stdbool.h>
#include <string.h>
#include "definitions.h"


#include <FillPat.h>
#include <LaunchPad.h>
#include <OrbitBoosterPackDefs.h>
#include <OrbitOled.h>
#include <OrbitOledChar.h>
#include <OrbitOledGrph.h>

#define SWITCH_COUNT        2
#define BUTTON_COUNT        2
#define MAX_SCREEN_PIXEL_X  128
#define MAX_SCREEN_PIXEL_Y  32
#define CHAR_PIXEL          8
#define GRID_X              16
#define GRID_Y              4

static int CursorPos_x = 8, CursorPos_y = 8;      //pos on screen (pixels)
static int GridPos_X = 1, GridPos_Y = 1;          //pos on grid (each point is 8 pixels);
static int level = 1;
static struct levelMap Curr_level;

static bool roomOverlaps (struct position pos[], int x1, int y1, int x2, int y2);
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

static enum GameMenu {
  Welcome,
  Game,
} gameCurrentPage = Welcome;

static void handlePlayerMovement() {
  /*
  CursorPos_x = GridPos_X*CHAR_PIXEL;
  CursorPos_y = GridPos_Y*CHAR_PIXEL;
  OrbitOledMoveTo(CursorPos_x,CursorPos_y);
  OrbitOledDrawChar('@');
  OrbitOledUpdate();
  OrbitOledClearBuffer();

  if (gameInputState.directions[3]) {
    GridPos_X++;
  } else if (gameInputState.directions[2]){
    GridPos_X--;
  } else if (gameInputState.directions[1]) {
      GridPos_Y++;
  } else if (gameInputState.directions[0]) {
      GridPos_Y--;
  }

  if (GridPos_X > 14) {
    GridPos_X--;
  }
  if (GridPos_X < 1) {
    GridPos_X++;
  }
  if (GridPos_Y < 1) {
    GridPos_Y++;
  }
  if (GridPos_Y > 2) {
    GridPos_Y--;
  }
  */
}

static void handleInput() {

  int surroundings[3][3] = {0};
  for (int x = Curr_level.usr.pos.x-1; x <= Curr_level.usr.pos.x+1; x++) {
    for (int y = Curr_level.usr.pos.y-1; y <= Curr_level.usr.pos.y+1; y++) {
      if (x<=0 || y<=0 || x >=Curr_level.len || y >= Curr_level.wid) {
        surroundings[y-Curr_level.usr.pos.y+1][x-Curr_level.usr.pos.x+1] = 1;
        continue;
      }
      for (int i = 0; i < Curr_level.roomCount; i++) {
        if (x==Curr_level.monsters[i].pos.x && y==Curr_level.monsters[i].pos.y) {
          surroundings[y-Curr_level.usr.pos.y+1][x-Curr_level.usr.pos.x+1] = 1;
          break;
        }
        if ((x==Curr_level.rooms[i].pos[0].x || x==Curr_level.rooms[i].pos[1].x) &&
            (y >= Curr_level.rooms[i].pos[0].y && y <= Curr_level.rooms[i].pos[1].y)) {
          surroundings[y-Curr_level.usr.pos.y+1][x-Curr_level.usr.pos.x+1] = 1;
          break;
        }
        if ((y==Curr_level.rooms[i].pos[0].y || y==Curr_level.rooms[i].pos[1].y) &&
            (x >= Curr_level.rooms[i].pos[0].x && x <= Curr_level.rooms[i].pos[1].x)) {
          surroundings[y-Curr_level.usr.pos.y+1][x-Curr_level.usr.pos.x+1] = 1;
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
      if (surroundings[0][1]!=1) updatePlayerPosition(&Curr_level.usr, gameInputState.tiltDirection);
      break;
    case DOWN:
      if (surroundings[2][1]!=1) updatePlayerPosition(&Curr_level.usr, gameInputState.tiltDirection);
      break;   
    case LEFT:
      if (surroundings[1][0]!=1) updatePlayerPosition(&Curr_level.usr, gameInputState.tiltDirection);
      break;
    case RIGHT:
      if (surroundings[1][2]!=1) updatePlayerPosition(&Curr_level.usr, gameInputState.tiltDirection);
      break;
    default:
      break;
  }
  
  
  
}


static void renderView() {
  OrbitOledClearBuffer();
  
  int sx1 = Curr_level.usr.pos.x-8;
  int sy1 = Curr_level.usr.pos.y-2;
  int sx2 = Curr_level.usr.pos.x+8;
  int sy2 = Curr_level.usr.pos.y+1;

  if(sx1 < 0 || sy1<0 || sx2 > Curr_level.len || sy2 > Curr_level.wid) {
    if (sx1 < 0 || sx2 > Curr_level.len) {
      int x;
      if (sx1 < 0) x = 0;
      else x = Curr_level.len;
      for (int y = 1; y < Curr_level.wid-1; y++) {
        OrbitOledMoveTo((x-sx1)*CHAR_PIXEL, (y-sy1)*CHAR_PIXEL);
        OrbitOledDrawChar('|');
      }
    }
  if (sy1 < 0 || sy2 > Curr_level.wid) {
      int y;
      if (sy1 < 0) y = 0;
      else y = Curr_level.wid;
      for (int x = 0; x < Curr_level.len; x++) {
        OrbitOledMoveTo((x-sx1)*CHAR_PIXEL, (y-sy1)*CHAR_PIXEL);
        OrbitOledDrawChar('-');
      }
    }
  }
  
  for (int i = 0; i < Curr_level.roomCount; i++) {
    if (roomOverlaps(
          Curr_level.rooms[i].pos,
          Curr_level.usr.pos.x-8,
          Curr_level.usr.pos.y-2,
          Curr_level.usr.pos.x+8,
          Curr_level.usr.pos.y+1
        )
    ) 
    {  
      if 
      (
        Curr_level.monsters[i].pos.x >= sx1 &&
        Curr_level.monsters[i].pos.x <= sx2 &&
        Curr_level.monsters[i].pos.y >= sy1 &&
        Curr_level.monsters[i].pos.y <= sy2
      ) {
        OrbitOledMoveTo((Curr_level.monsters[i].pos.x-sx1)*CHAR_PIXEL, (Curr_level.monsters[i].pos.y-sy1)*CHAR_PIXEL);
        OrbitOledDrawChar(Curr_level.monsters[i].name);
      }
      
      for (int x = Curr_level.rooms[i].pos[0].x; x <= Curr_level.rooms[i].pos[1].x; x++) {
        for (int y = Curr_level.rooms[i].pos[0].y; y <= Curr_level.rooms[i].pos[1].y; y++) {
          if (x >= sx1 && x <=sx2 && y>=sy1 && y<=sy2 && (x!=Curr_level.monsters[i].pos.x || y!=Curr_level.monsters[i].pos.y)) {
            if ((x==Curr_level.rooms[i].pos[0].x || x==Curr_level.rooms[i].pos[1].x) &&
                (y!=Curr_level.rooms[i].pos[0].y && y!=Curr_level.rooms[i].pos[1].y)) {
                OrbitOledMoveTo((x-sx1)*CHAR_PIXEL, (y-sy1)*CHAR_PIXEL);
                OrbitOledDrawChar('|');
            }
            else if (y==Curr_level.rooms[i].pos[0].y || y==Curr_level.rooms[i].pos[1].y) {
                OrbitOledMoveTo((x-sx1)*CHAR_PIXEL, (y-sy1)*CHAR_PIXEL);
                OrbitOledDrawChar('-');
            }
            else {
              OrbitOledMoveTo((x-sx1)*CHAR_PIXEL, (y-sy1)*CHAR_PIXEL);
              OrbitOledDrawChar('.');
            }
          }
        }
      }
    }
  }
  for (int i = 0; i < Curr_level.roomCount; i++) {

  }
  OrbitOledMoveTo((Curr_level.usr.pos.x-sx1)*CHAR_PIXEL, (Curr_level.usr.pos.y-sy1)*CHAR_PIXEL);
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
  default:
    break;
  }
  OrbitOledUpdate();
}

//initialize oled screen
void GameUIInit() {
  OrbitOledInit();
  OrbitOledClear();
  OrbitOledClearBuffer();
  OrbitOledSetFillPattern(OrbitOledGetStdPattern(iptnSolid));
  OrbitOledSetDrawMode(modOledSet);
  OrbitOledSetCharUpdate(0);
  Curr_level = CreateLevel(level);
}




