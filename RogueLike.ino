#include <delay.h>

//Forward Declarations
void GameUIInit();
void GameUITick();
void InputInit();
void ReadInput();
void CreateWorld();

extern const uint32_t Potentiometer;


void setup() {

  Serial.begin(9600);
  
  InputInit();
  GameUIInit();
  
  srand(analogRead(Potentiometer));
  
}

void loop() {

  ReadInput();
  GameUITick();

}
