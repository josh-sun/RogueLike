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
#define MAX_ROOM_SIZE_X     16
#define MAX_ROOM_SIZE_Y     4

static int CursorPos_x = 8, CursorPos_y = 8;      //pos on screen (pixels)
static int GridPos_X = 1, GridPos_Y = 1;          //pos on grid (each point is 8 pixels);
static int level = 1;
static struct levelMap Curr_level;

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

static void drawRoom() {
  
  
}

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


static void handlePageWelcome(){
 
  OrbitOledMoveTo(8, 0);
  OrbitOledDrawString("--Dungeon RPG--");
  
  OrbitOledMoveTo(0, 10);
  OrbitOledDrawString("BTN1 - Start");
  
  if(gameInputState.buttons[0].isRising) 
    gameCurrentPage = Game;

}

static void renderView() {
  OrbitOledClearBuffer();
  int player_x = Curr_level.usr.pos.x;
  int player_y = Curr_level.usr.pos.y;

}

void PageSelection() {
  
  switch(gameCurrentPage)
  {
  case Welcome:
    handlePageWelcome();
    break;
  case Game:
    renderView();
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




