#include <delay.h>


//Forward Declarations
void GameControllerInit();
void RenderView();
void InputInit();
void ReadInput();
void AccelerometerInit();

extern const uint32_t Potentiometer;
unsigned long t1;

void setup() {

  Serial.begin(9600);
  InputInit();
  AccelerometerInit();
  GameControllerInit();
  t1 = millis();

}

void loop() {
  ReadInput();
  PageSelection();
}
