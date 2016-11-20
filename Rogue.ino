#include <delay.h>
#include <FillPat.h>
#include <LaunchPad.h>
#include <OrbitBoosterPackDefs.h>
#include <OrbitOled.h>
#include <OrbitOledChar.h>
#include <OrbitOledGrph.h>
#include <stdlib.h>




void GameUIInit();
void WireInit();



void setup() {
    WireInit();
    Serial.begin(9600);

    delay(100);

    GameUIInit();

}

void loop() {
  // put your main code here, to run repeatedly: 
  GameUITick();
}
