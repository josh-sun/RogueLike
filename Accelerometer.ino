#include <Wire.h>


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
#define ADXL345_MAX_READING     255.0   // Max Value Sensor Could Read
#define MG_LSB                  0.00390625  //conversion Factor for Full-Res Setting

static byte buffer[ADXL345_DATA_SIZE];
static double rawData[ADXL345_AXIS_COUNT];
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
    writeToI2C(ADXL345_DATA_FORMAT, 0x09);
}

//************************Read Accerleration*************************
void get_xyz(double *xyz){
    readAccelG(xyz);
}

static void readAccel() {
    
    readFromI2C(ADXL345_DATAX0, buffer, 6);
    
    rawData[0] = (((int)buffer[1]) << 8) | buffer[0];
    rawData[1] = (((int)buffer[3]) << 8) | buffer[2];
    rawData[2] = (((int)buffer[5]) << 8) | buffer[4];
    
}

static void readAccelG (double *xyz) {
    readAccel();
    
    xyz[0] = rawData[0] * MG_LSB + offset_x;
    xyz[1] = rawData[1] * MG_LSB + offset_y;
    xyz[2] = rawData[2] * MG_LSB + offset_z;
    
    for(int i=0; i<3; i++){
        if (xyz[i] > ADXL345_MAX_READING || xyz[i] < 0) xyz[i] = 0;
    }
    
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

static void readFromI2C(byte address, byte *buffer, int amount) {
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
