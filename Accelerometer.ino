#include <Wire.h>
#include <math.h>

#define byte uint8_t

//register map
#define ADXL345_DEVICE_ADDRESS  0x1D    // Device Address
#define ADXL345_POWER_CTL       0x2D    // Power-Saving Features Control
#define ADXL345_DATA_FORMAT     0x31    // Data Format Control

#define ADXL345_DATAX0          0x32    // X-Axis Data 0
#define ADXL345_DATAX1          0x33    // X-Axis Data 1
#define ADXL345_DATAY0          0x34    // Y-Axis Data 0
#define ADXL345_DATAY1          0x35    // Y-Axis Data 1
#define ADXL345_DATAZ0          0x36    // Z-Axis Data 0
#define ADXL345_DATAZ1          0x37    // Z-Axis Data 1

//constant definition
#define ADXL345_DATA_SIZE       6       // Data Size From 6 Registers
#define ADXL345_AXIS_COUNT      3       // Number Of Axis
#define ADXL345_MAX_READING     2       // Max G Detection
#define MG_LSB                  0.00390625  //conversion Factor for Full-Res Setting

//Directions
static bool UP = false, DOWN = false, LEFT = false, RIGHT = false;

static uint32_t buffer[ADXL345_DATA_SIZE];
static uint16_t rawData[ADXL345_AXIS_COUNT];
static double offset_x, offset_y, offset_z;   //Software Offset

static TwoWire myWire(0);

//************************Initialization*************************
void AccelerometerInit() {
    myWire.begin();
    powerOn();
    setGRange();
    setSoftwareOffset(0.0,-0.04,0.07);
}

static void powerOn() {
    writeToI2C(ADXL345_POWER_CTL, 0x08);
}

static void setGRange() {
    writeToI2C(ADXL345_DATA_FORMAT, 0x08);
}

//************************Read Accerleration*************************
double *get_xyz(double *xyz){
    return readAccelG(xyz);
}

static void readAccel() {
    
    readFromI2C(ADXL345_DATAX0, buffer, 6);
    
    rawData[0] = (((int)buffer[1]) << 8) | buffer[0];
    rawData[1] = (((int)buffer[3]) << 8) | buffer[2];
    rawData[2] = (((int)buffer[5]) << 8) | buffer[4];
    
}

static double *readAccelG (double *xyz) {
    readAccel();
    
    xyz[0] = *(int16_t*)(&rawData[0]) * MG_LSB + offset_x;
    xyz[1] = *(int16_t*)(&rawData[1]) * MG_LSB + offset_y;
    xyz[2] = *(int16_t*)(&rawData[2]) * MG_LSB + offset_z;
    
    return xyz;
}
//************************ Sense pitch and rolls ************************
void getPitchRoll(double *xyz) {
  double pitch, roll;
  double limit = 25; //I still need to define the variables (booleans?) for up down left and right
  roll = (atan2(xyz[0],sqrt(xyz[1]*xyz[1]+xyz[2]*xyz[2])) * 180.0) / PI;
  pitch = (atan2(xyz[1],sqrt(xyz[0]*xyz[0]+xyz[2]*xyz[2])) * 180.0) / PI;
  if(pitch > limit) DOWN = true;
  else DOWN = false;
  if(pitch < - limit) UP = true;
  else UP = false;
  if(roll > limit) { LEFT = true;
  }else LEFT = false;
  if(roll < -limit) RIGHT = true;
  else RIGHT = false;
  /*
  Serial.print("Roll: ");
  Serial.print(atan2(xyz[0],sqrt(xyz[1]*xyz[1]+xyz[2]*xyz[2])));
  Serial.print(" Pitch: ");
  Serial.println(atan2(xyz[1],sqrt(xyz[0]*xyz[0]+xyz[2]*xyz[2])));
  */

}

bool getUpPitch () {
  return UP;
}

bool getDownPitch() {
  return DOWN;
}

bool getRightRoll() {
  return RIGHT;
}

bool getLeftRoll() {
  return LEFT;
}

//************************Software Offset Setter*************************
static void setSoftwareOffset (double x, double y, double z) {
    offset_x = x;
    offset_y = y;
    offset_z = z;
}

//********************************I2C R/W********************************
static void writeToI2C(byte address, byte val) {
    myWire.beginTransmission(ADXL345_DEVICE_ADDRESS);
    myWire.write(address);
    myWire.write(val);
    myWire.endTransmission();
}

static void readFromI2C(byte address, uint32_t *buffer, int amount) {
    myWire.beginTransmission(ADXL345_DEVICE_ADDRESS);
    myWire.write(address);
    myWire.endTransmission();
    
    myWire.beginTransmission(ADXL345_DEVICE_ADDRESS);
    myWire.requestFrom(ADXL345_DEVICE_ADDRESS, amount);  // Request 6 Bytes
    
    int i = 0;
    while(myWire.available()) // device may send less than requested (abnormal)
    {
        buffer[i] = myWire.read(); // receive a byte
        i++;
    }
    
    myWire.endTransmission();
}

//********************************Output Data********************************
