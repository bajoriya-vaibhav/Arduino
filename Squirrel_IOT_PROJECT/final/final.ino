#include <CapacitiveSensor.h>
#include <Wire.h> 
#include <Stepper.h>
#include <LiquidCrystal_I2C.h>
#define INTERVAL 100

bool touchRead(int pin){
  int val = 0;
  for(int i=0;i<5000;i++){
    val+=digitalRead(pin);
  }
  if(val>=4900){
    return 1;
  }
  else return 0;
}

// Timer state for each motor
unsigned long timer1 = 0;
unsigned long timer2 = 0;
unsigned long timer3 = 0;

// I2C LCD address -  0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

//number of steps per revolution
const int stepsPerRevolution = 200;

CapacitiveSensor touch1 = CapacitiveSensor(7,9);
CapacitiveSensor touch2 = CapacitiveSensor(2,5);
// CapacitiveSensor touch3 = CapacitiveSensor(8,11);

int threshold1 = 500;
int threshold2 = 500;

// 1ml==5cm
// 8200steps == 10ml;
double MAX_VOL = 10;

// Initialize the stepper motor object
// Stepper StepperB(stepsPerRevolution, 9, 8);
// Stepper StepperA(stepsPerRevolution, 10, 11);
// Stepper StepperC(stepsPerRevolution, 12, 13);

Stepper StepperA(stepsPerRevolution, 4 , 3);
Stepper StepperB(stepsPerRevolution, 6, 13);
// Stepper StepperC(stepsPerRevolution, 10, 12);

//pin connections
const int speed1 = A0;
const int volume1 = A1;
const int speed2 = A6;
const int volume2 = A7;
const int speed3 = A2;
const int volume3 = A3;

// steps used
int stepsA = 0;
int stepsB = 0;
int stepsC = 0;

void Stepper1() {
  long sensorValue1 = touch1.capacitiveSensor(30);
  int steps = Steps(Vol(analogRead(volume1)));
  
  Serial.println("A");

  // If squirrel and the volume is set more than previous volume used
  if (sensorValue1>threshold1 && steps-stepsA>10) {
    long startTime = millis();
    for(;stepsA<steps;stepsA+=10){
      steps = Steps(Vol(analogRead(volume1)));
      int motorSpeed = Speed(int(analogRead(speed1)));
      StepperA.setSpeed(motorSpeed);
      StepperA.step(10); 
      Serial.println(stepsA);

      // display
      int volume = Vol(analogRead(volume1));
      lcd.setCursor(4,0);
      lcd.print("A");
      if (motorSpeed < 10) {
        lcd.print("  ");
      }
      else if (motorSpeed < 100) {
        lcd.print(" ");
      }
      lcd.print(motorSpeed);
      lcd.setCursor(5,1);
      if (volume < 10) {
        lcd.print(" ");
      }
      lcd.print(volume);

      // check for the timer and sensor
      long time = millis();
      // Serial.println(time);
      if(time - startTime  > INTERVAL)return;
    }
    StepperA.step(stepsA-steps);
    stepsA=steps; 
  }
  // condition for reseting  
  else if(stepsA-steps>10){
    long startTime = millis();
    for(;steps-stepsA<10;stepsA-=10){
      steps = Steps(Vol(analogRead(volume1)));
      int motorSpeed = Speed(int(analogRead(speed1)));
      StepperA.setSpeed(motorSpeed);
      StepperA.step(-10); 
      Serial.println(stepsA);

      // display
      int volume = Vol(analogRead(volume1));
      lcd.setCursor(4,0);
      lcd.print("A");
      if (motorSpeed < 10) {
        lcd.print("  ");
      }
      else if (motorSpeed < 100) {
        lcd.print(" ");
      }
      lcd.print(motorSpeed);
      lcd.setCursor(5,1);
      if (volume < 10) {
        lcd.print(" ");
      }
      lcd.print(volume);
      // check for timer
      long time = millis();
      if(time - startTime  > INTERVAL)return;
    }
    StepperA.step(steps-stepsA);
    stepsA = steps;
  }
}

void Stepper2() {
  long sensorValue2 = touch2.capacitiveSensor(30);
  int steps = Steps(Vol(analogRead(volume2)));
  
  Serial.println("B");

  // If squirrel and the volume is set more than previous volume used
  if (sensorValue2>threshold2 && steps-stepsB>10) {
    long startTime = millis();
    for(;stepsB<steps;stepsB+=10){
      steps = Steps(Vol(analogRead(volume2)));
      int motorSpeed = Speed(int(analogRead(speed2)));
      StepperB.setSpeed(motorSpeed);
      StepperB.step(10); 
      Serial.println(stepsB);

      // display
      int volume = Vol(analogRead(volume2));
      lcd.setCursor(8,0);
      lcd.print("B");
      if (motorSpeed < 10) {
        lcd.print("  ");
      }
      else if (motorSpeed < 100) {
        lcd.print(" ");
      }
      lcd.print(motorSpeed);
      lcd.setCursor(9,1);
      if (volume < 10) {
        lcd.print(" ");
      }
      lcd.print(volume);

      // check for the timer and sensor
      long time = millis();
      // Serial.println(time);
      if(time - startTime  > INTERVAL)return;
    }
    StepperB.step(stepsB-steps);
    stepsB=steps; 
  }
  // condition for reseting  
  else if(stepsB-steps>10){
    long startTime = millis();
    for(;steps-stepsB<10;stepsB-=10){
      steps = Steps(Vol(analogRead(volume2)));
      int motorSpeed = Speed(int(analogRead(speed2)));
      StepperB.setSpeed(motorSpeed);
      StepperB.step(-10); 
      Serial.println(stepsB);
      // display
      int volume = Vol(analogRead(volume2));
      lcd.setCursor(8,0);
      lcd.print("B");
      if (motorSpeed < 10) {
        lcd.print("  ");
      }
      else if (motorSpeed < 100) {
        lcd.print(" ");
      }
      lcd.setCursor(9,1);
      if (volume < 10) {
        lcd.print(" ");
      }
      lcd.print(volume);
      // check for timer
      long time = millis();
      if(time - startTime > INTERVAL)return;
    }
    StepperB.step(steps-stepsB);
    stepsB = steps;
  }
}

// void Stepper3() {
//   long sensorValue3 = touch3.capacitiveSensor(30);
//   int steps = Steps(Vol(analogRead(volume3)));
  
//   Serial.println("C");
//   // If squirrel and the volume is set more than previous volume used
//   if (sensorValue3>threshold1 && steps-stepsC>10) {
//     long startTime = millis();
//     for(;stepsC<steps;stepsC+=10){
//       steps = Steps(Vol(analogRead(volume3)));
//       double motorSpeed = Speed(int(analogRead(speed3)));
//       StepperC.setSpeed(motorSpeed);
//       StepperC.step(10); 
//       Serial.println(stepsC);

//       // display
//       int volume = Vol(analogRead(volume3));
//       lcd.setCursor(12,0);
//       lcd.print("C");
//       if (motorSpeed < 10) {
//         lcd.print("  ");
//       }
//       else if (motorSpeed < 100) {
//         lcd.print(" ");
//       }
//       lcd.setCursor(14,1);
//       if (volume < 10) {
//         lcd.print(" ");
//       }
//       lcd.print(volume);
//       //  check for the timer and sensor
//       long time = millis();
//       // Serial.println(time);
//       if(time - startTime  > INTERVAL)return;
//     }
//     StepperC.step(stepsC-steps);
//     stepsC=steps; 
//   }
//   // condition for reseting  
//   else if(stepsC-steps>10){
//     long startTime = millis();
//     for(;steps-stepsC<10;stepsC-=10){
//       Serial.println(stepsA);
//       steps = Steps(Vol(analogRead(volume3)));
//       double motorSpeed = Speed(int(analogRead(speed3)));
//       int volume = Vol(analogRead(volume3));
//       lcd.setCursor(13,0);
//       lcd.print("C");
//       if (motorSpeed < 10) {
//         lcd.print("  ");
//       }
//       else if (motorSpeed < 100) {
//         lcd.print(" ");
//       }
//       lcd.setCursor(14,1);
//       if (volume < 10) {
//         lcd.print(" ");
//       }
//       lcd.print(volume);
//       StepperC.setSpeed(motorSpeed);
//       StepperC.step(-10); 
//       Serial.println(stepsC);
//       // check for timer
//       long time = millis();
//       if(time - startTime > INTERVAL)return;
//     }
//     StepperC.step(steps-stepsC);
//     stepsC = steps;
//   }
// }

// map for pot value to speed in rpm
double Speed(int potValue) {
  //speed range (0 to 60 rpm)
  double rpm = map(potValue, 0, 1023, 60, 120); 
  return rpm;
}

// map for pot value to volume in ml
double Vol(int v)
{
  double x = MAX_VOL*v/1024;
  return x;
}

// number of steps required
int Steps(double v)
{
  return stepsPerRevolution*4.1*v;
}

void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("RPM");
  lcd.setCursor(0, 1);
  lcd.print("Vol");
}


void loop() {
  long sensorValue1 = touch1.capacitiveSensor(30);
  long sensorValue2 = touch2.capacitiveSensor(30);
  // long sensorValue3 = touch3.capacitiveSensor(30);

  // lcd.setCursor(0, 0);
  // lcd.print(sensorValue1);
  // lcd.print("  ");
  // lcd.setCursor(6,0);
  // lcd.print(sensorValue2);
  // lcd.print("  ");
  // lcd.setCursor(0,1);
  // lcd.println(sensorValue3);

  // Serial.print(Speed(int(analogRead(speed1))));
  // Serial.print(" ");
  // Serial.print(Vol(analogRead(volume1)));
  // Serial.print(" ");
  // Serial.print(Speed(int(analogRead(speed2))));
  // Serial.print(" ");
  // Serial.print(Vol(analogRead(volume2)));
  // Serial.print(" ");
  // Serial.print(Speed(int(analogRead(speed3))));
  // Serial.print(" ");
  // Serial.println(Vol(analogRead(volume3)));
  // long sensorValue3 = touch3.capacitiveSensor(30);
  // Serial.println(sensorValue3);
  // Serial.println(digitalRead(4));
  // Stepper1();
  // Stepper2();
  // Stepper3();
  
}
