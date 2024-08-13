#include <Wire.h>

#define HUB_ADDRESS 0x68  

void setup() {
  Serial.begin(9600);
  Wire.begin();
}

void loop() {
  // Read data from IR Sensor 1
  int dataSensor1 = readIRSensor(0);
  Serial.print("IR Sensor 1 Data: ");
  Serial.println(dataSensor1);

  // Read data from IR Sensor 2
  int dataSensor2 = readIRSensor(1);
  Serial.print("IR Sensor 2 Data: ");
  Serial.println(dataSensor2);

  // Read data from IR Sensor 3
  int dataSensor3 = readIRSensor(2);
  Serial.print("IR Sensor 3 Data: ");
  Serial.println(dataSensor3);

  delay(1000);  // Adjust the delay based on your application
}

int readIRSensor(int sensorNumber) {
  // Command to request data from a specific IR sensor
  Wire.beginTransmission(HUB_ADDRESS);
  Wire.write(sensorNumber);  // Send the sensor number as a command
  Wire.endTransmission();

  // Request and read 2 bytes of data from the IR sensor
  Wire.requestFrom(HUB_ADDRESS, 2);
  if (Wire.available() == 2) {
    byte highByte = Wire.read();
    byte lowByte = Wire.read();
    int sensorData = (highByte << 8) | lowByte;
    return sensorData;
  } else {
    Serial.println("Error reading data from the IR sensor");
    return -1;  // Error value, adjust as needed
  }
}
