#include <Wire.h>

#define ADXL345_DEVICE_ADDRESS  0x1D    // Device Address

static TwoWire myWire(0);

void Wire_utils_init() {
  myWire.begin();
}

//********************************I2C R/W********************************
void writeToI2C(byte address, byte val) {
    myWire.beginTransmission(ADXL345_DEVICE_ADDRESS);
    myWire.write(address);
    myWire.write(val);
    myWire.endTransmission();
}

void readFromI2C(byte address, uint32_t *buffer, int amount) {
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
