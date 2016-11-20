

void AccelerometerInit();
void get_xyz(double *xyz);

void setup() {
  Serial.begin(9600);
  AccelerometerInit();
}

void loop() {
  double xyz[3] = {0};
  get_xyz(xyz);

 
  Serial.print("x:");
  Serial.print(xyz[0]);
  Serial.print(" y:");
  Serial.print(xyz[1]);
  Serial.print(" z:");
  Serial.println(xyz[2]);
  delay(100);
  
  
}
