#include <delay.h>

//Forward Declarations
void GameUIInit();
void GameUITick();
void InputInit();
void OnInput();
void CreateWorld();

extern const uint32_t Potentiometer;


void setup() {

  Serial.begin(9600);
  
  InputInit();
  GameUIInit();
  
  CreateWorld();
  
  srand(analogRead(Potentiometer));
  
}

void loop() {
  // put your main code here, to run repeatedly: 
  OnInput();
  GameUITick();

}
