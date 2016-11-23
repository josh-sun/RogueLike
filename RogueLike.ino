#include <delay.h>

//Forward Declarations
void GameUIInit();
void GameUITick();
void InputInit();
void OnInput();

extern const uint32_t Potentiometer;


void setup() {

  Serial.begin(9600);
  InputInit();
  GameUIInit();
  srand((7+analogRead(Potentiometer)) * 347);
}

void loop() {
  // put your main code here, to run repeatedly: 
  OnInput();
  GameUITick();

}
