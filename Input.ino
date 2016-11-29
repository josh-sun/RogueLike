
const uint32_t SwitchCount = 2;
const uint32_t ButtonCount = 2;
const uint32_t Switches[SwitchCount] = { PA_7, PA_6 };
const uint32_t Buttons[ButtonCount] = { PD_2, PE_1 };
const uint32_t Potentiometer = PE_3;

//Forward Declarations
double *ReadAccelG(double xyz[3]);
int CalcTiltDirection (double g);

void InputInit() {

  for(int i = 0; i < SwitchCount; ++i )
    pinMode(Switches[i], INPUT);
  for(int i = 0; i < ButtonCount; ++i )
    pinMode(Buttons[i], INPUT);
  
  srand((420+analogRead(Potentiometer)) * millis() * 1000 / 69);
  
}

void ReadInput() {

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
  double xyz[3];
  gameInputState.tiltDirection = CalcTiltDirection(ReadAccelG(xyz));
  
}
