#include <CapacitiveSensor.h>
#include <Wire.h> 
#include <Stepper.h>
#include <LiquidCrystal_I2C.h>

// I2C LCD address -  0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

CapacitiveSensor touch1 = CapacitiveSensor(5,2);
CapacitiveSensor touch2 = CapacitiveSensor(6,3);
CapacitiveSensor touch3 = CapacitiveSensor(7,4);

int threshold = 300;

// double MAX_LEN = 6;
// double MAX_VOL = 10;
// int DELAY_O = 500;

// steps required to complete one revolution
int stepsPerRevolution = 200;

// stepper objects
Stepper Stepper1(stepsPerRevolution, 8, 9);
Stepper Stepper2(stepsPerRevolution, 10, 11);
Stepper Stepper3(stepsPerRevolution, 12, 13);

// speed and volume control pins
const int speed1 = A0;
const int volume1 = A1;
const int speed2 = A2;
const int volume2 = A3;
const int speed3 = A4;
const int volume3 = A5;

