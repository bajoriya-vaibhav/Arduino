#include <CapacitiveSensor.h>

CapacitiveSensor touch1 = CapacitiveSensor(5,2);
CapacitiveSensor touch2 = CapacitiveSensor(6,3);
CapacitiveSensor touch3 = CapacitiveSensor(7,4);

int threshold = 300;

void setup() {
  Serial.begin(9600);
}

void loop() {
  long sensorValue1 = touch1.capacitiveSensor(30);
  long sensorValue2 = touch2.capacitiveSensor(30);
  long sensorValue3 = touch3.capacitiveSensor(30);

  Serial.print(sensorValue1);
  Serial.print(" ");
  Serial.print(sensorValue2);
  Serial.print(" ");
  Serial.println(sensorValue3);
  
//   if (sensorValue1 > threshold) {
//     // turn the motor of that sensor on

//   }
//   // if it's lower than the threshold
//   else {
//     // turn off the motor
//   }

// // if the value is greater than the threshold
//   if (sensorValue2 > threshold) {
//     // turn the motor2 on
//   }
//   // if it's lower than the threshold
//   else {
//     // turn it off
//   }

//   if (sensorValue3 > threshold) {
//     // turn the motor of that sensor on

//   }
//   // if it's lower than the threshold
//   else {
//     // turn off the motor
//   }
delay(100);
}