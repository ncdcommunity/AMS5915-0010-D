// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// AMS5915_0100_D
// This code is designed to work with the AMS5915_I2CS_0100-D I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/products

#include <Wire.h>

// AMS5915_0100_D I2C address is 0x28(40)
#define Addr 0x28

void setup()
{
  // Initialise I2C communication as MASTER
  Wire.begin();
  // Initialise serial communication, set baud rate = 9600
  Serial.begin(9600);
  delay(300);
}

void loop()
{
  unsigned int data[4];

  // Request 4 bytes of data
  Wire.requestFrom(Addr, 4);

  // Read 4 bytes of data
  // pressure msb, pressure lsb, temp msb, temp lsb
  if (Wire.available() == 4)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
    data[2] = Wire.read();
    data[3] = Wire.read();
  }

  // Convert the data
  float pressure = ((data[0] & 0x3F) * 256.0 + data[1]);
  float temp = ((data[2] & 0xFF) * 256.0 + (data[3] & 0xE0)) / 32;
  pressure = ((pressure - 1638.0) / ((13107.0) / 10.0));
  float cTemp = ((temp * 200.0) / 2048) - 50.0;
  float fTemp = (cTemp * 1.8 ) + 32;

  // Output data to serial monitor
  Serial.print("Pressure : ");
  Serial.print(pressure);
  Serial.println(" mbar");
  Serial.print("Temperature in Celsius : ");
  Serial.print(cTemp);
  Serial.println(" C");
  Serial.print("Temperature in Fahrenheit : ");
  Serial.print(fTemp);
  Serial.println(" F");
  delay(500);
}
