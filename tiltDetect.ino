

void AccelerometerInit();
double *get_xyz(double *xyz);

void TiltDetectInit() {
  AccelerometerInit();
}

void TiltDetectTick() {
  double *xyz = (double*)malloc(sizeof(double)*3);
  xyz = get_xyz(xyz);

  
  Serial.print("x: ");
  Serial.print(xyz[0]);
  Serial.print(" y: ");
  Serial.print(xyz[1]);
  Serial.print(" z: ");
  Serial.println(xyz[2]);
  
  getPitchRoll(xyz);
  free(xyz);
}

