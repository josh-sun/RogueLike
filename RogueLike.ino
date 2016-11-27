#include <delay.h>

//Forward Declarations
void GameUIInit();
void RenderView();
void InputInit();
void ReadInput();

extern const uint32_t Potentiometer;


void setup() {

  Serial.begin(9600);

  
  InputInit();
  srand(analogRead(Potentiometer));
  
  GameUIInit();
  

  
}

void loop() {
  PageSelection();
  ReadInput();

}
