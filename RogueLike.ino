#include <delay.h>


//Forward Declarations
void GameUIInit();
void RenderView();
void InputInit();
void ReadInput();

extern const uint32_t Potentiometer;
unsigned long time1;
unsigned long time2;

void setup() {

  Serial.begin(9600);
  

  
  InputInit();
  srand(analogRead(Potentiometer));
  
  GameUIInit();
  

  
}

void loop() {
  ReadInput();
  PageSelection();
  delay(200);

}
