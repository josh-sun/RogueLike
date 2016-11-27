#include <stdbool.h>
#include <string.h>

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

struct ButtonState { 
  bool state;
  bool isRising;
};

static struct InputState
{
  bool                switches[2];
  struct ButtonState  buttons[2];
  int                 tiltDirection;
  float               potentiometer;
} gameInputState;

static enum GameMenu {
  Welcome,
  Difficulty_Selection,
  Game,
} gameCurrentPage = Welcome;

//initialize oled screen
void GameUIInit() {
  OrbitOledInit();
  OrbitOledClear();
  OrbitOledClearBuffer();
  OrbitOledSetFillPattern(OrbitOledGetStdPattern(iptnSolid));
  OrbitOledSetDrawMode(modOledSet);
  OrbitOledSetCharUpdate(0);
  
  handlePageWelcome(); 
}

static void MapGenerate() {

  
}

static void drawRoom() {
  char roomMap [MAX_ROOM_SIZE_Y][MAX_ROOM_SIZE_X] = 
  { {'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'},
    {'|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|'},
    {'|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|'},
    {'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'}
  };

  for (int i = 0; i < MAX_ROOM_SIZE_X; i++ ) {
    for (int j = 0; j < MAX_ROOM_SIZE_Y; j++) {
      OrbitOledMoveTo(i*CHAR_PIXEL,j*CHAR_PIXEL);
      OrbitOledDrawChar(roomMap[j][i]);
    }
  }
  
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
  
  /*
  OrbitOledDrawRect(5, 5);
  OrbitOledFillRect(5, 5);
  */
  
    
  OrbitOledMoveTo(25, 0);
  OrbitOledDrawString("---Rogue---");
  
  OrbitOledMoveTo(0, 10);
  OrbitOledDrawString("BTN1 - Start");

  OrbitOledMoveTo(0, 20);
  OrbitOledDrawString("BTN2 - Tutorial");

  
  OrbitOledUpdate();
  OrbitOledClearBuffer();
  
  if(gameInputState.buttons[0].isRising) {
    gameCurrentPage = Game;
    //gameUiPage = SelectPlayers;
  }

  if(gameInputState.buttons[1].isRising) {
    OrbitOledMoveTo(5,0);
    OrbitOledDrawString("Tutorial");
    
  } 
}

void GameUITick() {
  
  switch(gameCurrentPage)
  {
  case Welcome:
    handlePageWelcome();
    break;
  case Difficulty_Selection:
    break;
  case Game:
    drawRoom();
    handlePlayerMovement();
    break;
  default:
    break;
  }
}




