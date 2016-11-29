#include <math.h>
#include "definitions.h"

//Forward Declarations
void Wire_utils_init();
void writeToI2C(byte address, byte val);
void readFromI2C(byte address, uint32_t *buffer, int amount);

//Register Map
#define ADXL345_POWER_CTL       0x2D          // Power-Saving Features Control
#define ADXL345_DATA_FORMAT     0x31          // Data Format Control
#define ADXL345_DATAX0          0x32          // X-Axis Data 0
#define ADXL345_DATAX1          0x33          // X-Axis Data 1
#define ADXL345_DATAY0          0x34          // Y-Axis Data 0
#define ADXL345_DATAY1          0x35          // Y-Axis Data 1
#define ADXL345_DATAZ0          0x36          // Z-Axis Data 0
#define ADXL345_DATAZ1          0x37          // Z-Axis Data 1

//Constants Definition
#define ADXL345_DATA_SIZE       6             // Data Size From 6 Registers
#define ADXL345_MAX_READING     2             // Max G Detection
#define MG_LSB                  0.00390625    // Conversion Factor for Full-Res Setting
#define TILT_THRESHOLD          15            // Threshold Value for Determining Tilt

static double offset_X, offset_Y, offset_Z;   // Software Offset Calibration

//************************Initialization*************************

void AccelerometerInit() {
    Wire_utils_init();
    powerOn(0x08);
    setGRange(0x08);
    setSoftwareOffset(0.0,-0.04,0.07);
}

static void powerOn(byte value) {
    writeToI2C(ADXL345_POWER_CTL, value);
}

static void setGRange(byte value) {
    writeToI2C(ADXL345_DATA_FORMAT, value);
}

//************************Read Accerleration*************************


double *ReadAccelG (double xyz[3]) {
    uint16_t rawData[3];
    
    readAccel(rawData);
    
    xyz[0] = *(int16_t*)(&rawData[0]) * MG_LSB + offset_X;
    xyz[1] = *(int16_t*)(&rawData[1]) * MG_LSB + offset_Y;
    xyz[2] = *(int16_t*)(&rawData[2]) * MG_LSB + offset_Z;

    return xyz;
}

static void readAccel(uint16_t *rawData) {

    uint32_t buffer[ADXL345_DATA_SIZE];

    readFromI2C(ADXL345_DATAX0, buffer, 6);
    
    rawData[0] = (((int)buffer[1]) << 8) | buffer[0];
    rawData[1] = (((int)buffer[3]) << 8) | buffer[2];
    rawData[2] = (((int)buffer[5]) << 8) | buffer[4];
    
}

//************************ Sense pitch and rolls ************************
int CalcTiltDirection(double xyz[3]) {
  
  double roll = (atan2(xyz[0],sqrt(xyz[1]*xyz[1]+xyz[2]*xyz[2])) * 180.0) / PI;
  double pitch = (atan2(xyz[1],sqrt(xyz[0]*xyz[0]+xyz[2]*xyz[2])) * 180.0) / PI;

  //up
  if(pitch < -TILT_THRESHOLD) 
    return UP;

  //down
  if(pitch > TILT_THRESHOLD) 
    return DOWN;

  //left  
  if(roll > TILT_THRESHOLD)
    return LEFT;

  //right
  if(roll < -TILT_THRESHOLD) 
    return RIGHT;

  return NO_TILT;
}

//************************Software Offset Setter*************************
static void setSoftwareOffset (double x, double y, double z) {
    offset_X = x;
    offset_Y = y;
    offset_Z = z;
}





