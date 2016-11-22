#include <delay.h>
#include <LaunchPad.h>
#include <OrbitBoosterPackDefs.h>





void GameUIInit();
void TiltDetectInit();
void AccelerometerInit();

void GameUITick();



void setup() {

    Serial.begin(9600);

    AccelerometerInit();
    TiltDetectInit();


    GameUIInit();

}

void loop() {
  // put your main code here, to run repeatedly: 
  GameUITick();
}
