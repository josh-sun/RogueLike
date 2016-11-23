#include <delay.h>

//Forward Declarations
void GameUIInit();
void GameUITick();
void AccelerometerInit();




void setup() {

    Serial.begin(9600);
    AccelerometerInit();
    GameUIInit();

}

void loop() {
  // put your main code here, to run repeatedly: 
  GameUITick();

}
