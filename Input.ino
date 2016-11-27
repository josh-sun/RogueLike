const uint32_t SwitchCount = 2;
const uint32_t ButtonCount = 2;
const uint32_t Switches[SwitchCount] = { PA_7, PA_6 };
const uint32_t Buttons[ButtonCount] = { PD_2, PE_1 };
const uint32_t Potentiometer = PE_3;

//Forward Declarations
double *ReadAccelG(double xyz[3]);
int CalcTiltDirection (double g);
void AccelerometerInit();


void InputInit() {
  AccelerometerInit();

  for(int i = 0; i < SwitchCount; ++i )
    pinMode(Switches[i], INPUT);
  for(int i = 0; i < ButtonCount; ++i )
    pinMode(Buttons[i], INPUT);
  
  srand((7+analogRead(Potentiometer)) * 347);
  
}

void ReadInput() {
  double xyz[3];
  for(int i = 0; i < SwitchCount; ++i )
    gameInputState.switches[i] = digitalRead(Switches[i]);
  for(int i = 0; i < ButtonCount; ++i )
  {
    // Only look for Rising Edge Signals.
    bool previousState = gameInputState.buttons[i].state;
    gameInputState.buttons[i].state = digitalRead(Buttons[i]);
    gameInputState.buttons[i].isRising = (!previousState && gameInputState.buttons[i].state);
  }
  gameInputState.potentiometer = analogRead(Potentiometer);
  gameInputState.tiltDirection = CalcTiltDirection(ReadAccelG(xyz));
}
