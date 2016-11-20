#include <stdbool.h>
#include <string.h>

static const uint32_t SwitchCount = 2;
static const uint32_t ButtonCount = 2;
static const uint32_t Switches[SwitchCount] = { PA_7, PA_6 };
static const uint32_t Buttons[ButtonCount] = { PD_2, PE_0 };

static const size_t dimensionsCount = 2;
static const int MaxMapSize[dimensionsCount] = {1280,320};
static int CursorPos[dimensionsCount] = {0};

static struct GameMap {
  int x_pos;
  int y_pos;
  int diameter;
} currentMap;

static enum GameMenu {
  Welcome,
  Difficulty_Selection,
  Game,
} gameCurrentPage = Welcome;

struct ButtonState { 
  bool state;
  bool isRising;
};

static struct InputState
{
  bool                switches[2];
  struct ButtonState  buttons[2];
  float               potentiometer;
} gameInputState;

static void MapGenerate() {
  
}


//initialize oled screen
void GameUIInit() {
  OrbitOledInit();
  OrbitOledClear();
  OrbitOledClearBuffer();
  OrbitOledSetFillPattern(OrbitOledGetStdPattern(iptnSolid));
  OrbitOledSetDrawMode(modOledSet);


  
  Serial.println("Game UI Initialzied");
  for(int i = 0; i < SwitchCount; ++i )
    pinMode(Switches[i], INPUT);
  for(int i = 0; i < ButtonCount; ++i )
    pinMode(Buttons[i], INPUT);    
}

static void handlePlayerMovement() {
  OrbitOledMoveTo(CursorPos[0],CursorPos[1]);
  OrbitOledDrawChar('@');
  
  if(gameInputState.buttons[0].isRising) {
    delay(50);
    OrbitOledClear();
    CursorPos[0]+=5;
  }

  if(gameInputState.buttons[1].isRising) {
    delay(50);
    OrbitOledClear();
    CursorPos[1]+=5;
  }


  
  /*
  if(gameInputState.buttons[1].isRising) {
        OrbitOledClearBuffer();
        OrbitOledClear();
        OrbitOledMoveTo(pos[0],++pos[1]);
        handleGameUI();
    }
    */
}


static void handlePageWelcome(){
  
  /*
  OrbitOledDrawRect(5, 5);
  OrbitOledFillRect(5, 5);
  */

  int a = 0;
    
  OrbitOledMoveTo(25, 0);
  OrbitOledDrawString("---Rogue---");
  
  OrbitOledMoveTo(0, 10);
  OrbitOledDrawString("BTN1 - Start");

  OrbitOledMoveTo(0, 20);
  OrbitOledDrawString("BTN2 - Tutorial");
  
  if(gameInputState.buttons[0].isRising) {
    OrbitOledClearBuffer();
    OrbitOledClear();
    OrbitOledMoveTo(0,0);
    OrbitOledDrawChar('@');
    gameCurrentPage = Game;
    //gameUiPage = SelectPlayers;
    
  }

  if(gameInputState.buttons[1].isRising) {
    OrbitOledClearBuffer();
    OrbitOledClear();
    OrbitOledMoveTo(5,0);
    OrbitOledDrawString("Tutorial");
    
  } 
}

static void GameUITick() {
  uiInputTick();
  
  switch(gameCurrentPage)
  {
  case Welcome:
    handlePageWelcome();
    break;
  case Difficulty_Selection:
    break;
  case Game:
    handlePlayerMovement();
    break;
  default:
    break;
  }
  OrbitOledUpdate();
}

static void uiInputTick() {
  for(int i = 0; i < SwitchCount; ++i )
    gameInputState.switches[i] = digitalRead(Switches[i]);
  for(int i = 0; i < ButtonCount; ++i )
  {
    // Only look for Rising Edge Signals.
    bool previousState = gameInputState.buttons[i].state;
    gameInputState.buttons[i].state = digitalRead(Buttons[i]);
    gameInputState.buttons[i].isRising = (!previousState && gameInputState.buttons[i].state);
  }
  //gameInputState.potentiometer = analogRead(Potentiometer);
}


