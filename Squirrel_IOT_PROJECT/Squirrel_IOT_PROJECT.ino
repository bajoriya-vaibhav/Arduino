#include <LiquidCrystal.h>
double MAX_LEN = 6;
double MAX_VOL = 10;
int DELAY_O = 1000;
int Sdist = 5;

// Define pin connections
const int dirPin1 = 7;
const int stepPin1 = 6;
const int dirPin2 = 5;
const int stepPin2 = 4; 
const int dirPin3 = 3;
const int stepPin3 = 2;
const int speed1 = A0;
const int volume1 = A1;
const int speed2 = A2;
const int volume2 = A3;
const int speed3 = A4;
const int volume3 = A5;
const int enter1 = A6;
const int enter2 = A7;
const int enter3 = A8;
const int powerMain = A9;
const int reset1 = A10;
const int reset2 = A11;
const int reset3 = A12;
const int Mainreset = A13;
// const int echo1 = 35;
// const int trig1 = 34;
// const int echo2 = 37;
// const int trig2 = 36;
// const int echo3 = 39;
// const int trig3 = 38;

// Bool variables
bool wait_1 = true;
bool wait_2 = true;
bool wait_3 = true;
bool reset_1 = false;
bool reset_2 = false;
bool reset_3 = false;
bool MainReset = false;

//LCDs
/* LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 */
const int rs_1 = 13, en_1 = 12, d4_1 = 11, d5_1 = 10, d6_1 = 9, d7_1 = 8;
LiquidCrystal lcd_1(rs_1, en_1, d4_1, d5_1, d6_1, d7_1);
const int rs_2 = 27, en_2 = 26, d4_2 = 25, d5_2 = 24, d6_2 = 23, d7_2 = 22;
LiquidCrystal lcd_2(rs_2, en_2, d4_2, d5_2, d6_2, d7_2);
const int rs_3 = 33, en_3 = 32, d4_3 = 31, d5_3 = 30, d6_3 = 29, d7_3 = 28;
LiquidCrystal lcd_3(rs_3, en_3, d4_3, d5_3, d6_3, d7_3);

void Stepper1(int d, int steps){
  digitalWrite(dirPin1, HIGH);
  int x = 0, y = 0;
  for(x = 0; x < steps; x++)
	{
    if(!reset_1){
      digitalWrite(stepPin1, HIGH);
      delayMicroseconds(1000);
      digitalWrite(stepPin1, LOW);
      delayMicroseconds(1000);
      if(x%d == 0) delay(DELAY_O);
    }
    else{
      digitalWrite(dirPin1, LOW);
      for(y = 0; y < x; y++){
        digitalWrite(stepPin1, HIGH);
        delayMicroseconds(1000);
        digitalWrite(stepPin1, LOW);
        delayMicroseconds(1000);
      }
      wait_1 = true;
      reset_1 = false;
      return;
    }
	}
  digitalWrite(dirPin1, LOW);
  for(x = 0; x < steps; x++)
	{
		digitalWrite(stepPin1, HIGH);
		delayMicroseconds(1000);
		digitalWrite(stepPin1, LOW);
		delayMicroseconds(1000);
	}
  wait_1 = true;
  return;
}

void Stepper2(int d, int steps){
  digitalWrite(dirPin2, HIGH);
  int x = 0, y = 0;
  for(x = 0; x < steps; x++)
	{
    if(!reset_2){
      digitalWrite(stepPin2, HIGH);
      delayMicroseconds(1000);
      digitalWrite(stepPin2, LOW);
      delayMicroseconds(1000);
      if(x%d == 0) delay(DELAY_O);
    }
    else{
      digitalWrite(dirPin2, LOW);
      for(y = 0; y < x; y++){
        digitalWrite(stepPin2, HIGH);
        delayMicroseconds(1000);
        digitalWrite(stepPin2, LOW);
        delayMicroseconds(1000);
      }
      wait_2 = true;
      reset_2 = false;
      return;
    }
	}
  digitalWrite(dirPin2, LOW);
  for(x = 0; x < steps; x++)
	{
		digitalWrite(stepPin2, HIGH);
		delayMicroseconds(1000);
		digitalWrite(stepPin2, LOW);
		delayMicroseconds(1000);
	}
  wait_2 = true;
  return;
}

void Stepper3(int d, int steps){
  digitalWrite(dirPin3, HIGH);
  int x = 0, y = 0;
  for(x = 0; x < steps; x++)
	{
    if(!reset_3){
      digitalWrite(stepPin3, HIGH);
      delayMicroseconds(1000);
      digitalWrite(stepPin3, LOW);
      delayMicroseconds(1000);
      if(x%d == 0) delay(DELAY_O);
    }
    else{
      digitalWrite(dirPin3, LOW);
      for(y = 0; y < x; y++){
        digitalWrite(stepPin3, HIGH);
        delayMicroseconds(1000);
        digitalWrite(stepPin3, LOW);
        delayMicroseconds(1000);
      }
      wait_3 = true;
      reset_3 = false;
      return;
    }
	}
  digitalWrite(dirPin3, LOW);
  for(x = 0; x < steps; x++)
	{
		digitalWrite(stepPin3, HIGH);
		delayMicroseconds(1000);
		digitalWrite(stepPin3, LOW);
		delayMicroseconds(1000);
	}
  wait_3 = true;
  return;
}

double speed(int d)
{
  double x = -1*(19*MAX_LEN*d*330)/(100*1024);
  return x;
}

double dist(int v)
{
  double x = (MAX_LEN*v*330)/1024;
  return x;
}

double vol(int v)
{
  double x = MAX_VOL*v/1024;
  return x;
}

// int dist_ultra(int x)
// {
//   if(x == 1) {
//     digitalWrite(trig1, LOW);
//     delayMicroseconds(2);
//     digitalWrite(trig1, HIGH);
//     delayMicroseconds(10);
//     digitalWrite(trig1, LOW);
//     long duration = pulseIn(echo1, HIGH);
//     int distance = duration * 0.034 / 2;
//     return distance;
//   }
//   else if(x == 2) {
//     digitalWrite(trig2, LOW);
//     delayMicroseconds(2);
//     digitalWrite(trig2, HIGH);
//     delayMicroseconds(10);
//     digitalWrite(trig2, LOW);
//     long duration = pulseIn(echo2, HIGH);
//     int distance = duration * 0.034 / 2;
//     return distance;
//   }
//   else if(x == 3) {
//     digitalWrite(trig3, LOW);
//     delayMicroseconds(2);
//     digitalWrite(trig3, HIGH);
//     delayMicroseconds(10);
//     digitalWrite(trig3, LOW);
//     long duration = pulseIn(echo3, HIGH);
//     int distance = duration * 0.034 / 2;
//     return distance;
//   }
// }

void setup() {
  lcd_1.begin(16, 2);
  lcd_2.begin(16, 2);
  lcd_3.begin(16, 2);
  pinMode(stepPin1, OUTPUT);
	pinMode(dirPin1, OUTPUT);
  pinMode(stepPin2, OUTPUT);
	pinMode(dirPin2, OUTPUT);
  pinMode(stepPin3, OUTPUT);
	pinMode(dirPin3, OUTPUT);
  // pinMode(trig1, OUTPUT);
  // pinMode(echo1, INPUT);
  // pinMode(trig2, OUTPUT);
  // pinMode(echo2, INPUT);
  // pinMode(trig3, OUTPUT);
  // pinMode(echo3, INPUT);
}

void loop() {
  if(analogRead(powerMain) > 500)
  {
    if(analogRead(Mainreset) > 500) 
    {
      MainReset = true;
    }
    else MainReset = false;
    if(!MainReset)
    {
      // Motor 1
      if(analogRead(reset1) > 500) {
        reset_1 = true;
      }
      if(!reset_1)
      {
        if(wait_1)
        {
          if(analogRead(enter1) > 500)
          {
            wait_1 = false;
          }
          else
          {
            lcd_1.clear();
            lcd_1.setCursor(0,0);
            lcd_1.print("Speed: " + String(speed(analogRead(speed1))));
            lcd_1.setCursor(0,1);
            lcd_1.print("Vol: " + String(vol(analogRead(volume1))));
          }
        }
        else
        {
          lcd_1.clear();
          lcd_1.setCursor(0,0);
          lcd_1.print("M1 is Running");
          // int d1 = dist_ultra(1);
          // if(d1 < Sdist) {
          //   lcd_1.setCursor(0,1);
          //   lcd_1.print("Dist: " + String(d1) + " near");
          //   Stepper1(int(speed(analogRead(speed1))),int(dist(analogRead(volume1))));
          // }
          // else {
          //   lcd_1.setCursor(0,1);
          //   lcd_1.print("Dist: " + String(d1) + " far");
          // }
        }
      }
      else
      {
        lcd_1.clear();
        lcd_1.setCursor(0,0);
        lcd_1.print("Motor1 is ");
        lcd_1.setCursor(0,1);
        lcd_1.print("Restarting-1");
      }
      
      // Motor 2
      if(analogRead(reset2) > 500) {
        reset_2 = true;
      }
      if(!reset_2)
      {
        if(wait_2)
        {
          if(analogRead(enter2) > 500)
          {
            wait_2 = false;
          }
          else
          {
            lcd_2.clear();
            lcd_2.setCursor(0,0);
            lcd_2.print("Speed: " + String(speed(analogRead(speed2))));
            lcd_2.setCursor(0,1);
            lcd_2.print("Vol: " + String(vol(analogRead(volume2))));
          }
        }
        else
        {
          lcd_2.clear();
          lcd_2.setCursor(0,0);
          lcd_2.print("M2 is Running");
          // int d2 = dist_ultra(2);
          // if(d2 < Sdist) {
          //   lcd_2.setCursor(0,1);
          //   lcd_2.print("Dist: " + String(d2) + " near");
          //   Stepper2(int(speed(analogRead(speed2))),int(dist(analogRead(volume2))));
          // }
          // else {
          //   lcd_2.setCursor(0,1);
          //   lcd_2.print("Dist: " + String(d2) + " far");
          // }
        }
      }
      else
      {
        lcd_2.clear();
        lcd_2.setCursor(0,0);
        lcd_2.print("Motor2 is ");
        lcd_2.setCursor(0,1);
        lcd_2.print("Restarting-2");
      }

      // Motor 3
      if(analogRead(reset3) > 500) {
        reset_3 = true;
      }
      if(!reset_3)
      {
        if(wait_3)
        {
          if(analogRead(enter3) > 500)
          {
            wait_3 = false;
          }
          else
          {
            lcd_3.clear();
            lcd_3.setCursor(0,0);
            lcd_3.print("Speed: " + String(speed(analogRead(speed3))));
            lcd_3.setCursor(0,1);
            lcd_3.print("Vol: " + String(vol(analogRead(volume3))));
          }
        }
        else
        {
          lcd_3.clear();
          lcd_3.setCursor(0,0);
          lcd_3.print("M3 is Running");
          // int d3 = dist_ultra(3);
          // if(d3 < Sdist) {
          //   lcd_3.setCursor(0,1);
          //   lcd_3.print("Dist: " + String(d3) + " near");
          //   Stepper3(int(speed(analogRead(speed3))),int(dist(analogRead(volume3))));
          // }
          // else {
          //   lcd_3.setCursor(0,1);
          //   lcd_3.print("Dist: " + String(d3) + " far");
          // }
        }
      }
      else
      {
        lcd_3.clear();
        lcd_3.setCursor(0,0);
        lcd_3.print("Motor3 is ");
        lcd_3.setCursor(0,1);
        lcd_3.print("Restarting-3");
      }
    }
    else
    {
      reset_1 = true;
      reset_2 = true;
      reset_3 = true;

      lcd_1.clear();
      lcd_1.setCursor(0,0);
      lcd_1.print("Motor1 is ");
      lcd_1.setCursor(0,1);
      lcd_1.print("Restarting");
      
      lcd_2.clear();
      lcd_2.setCursor(0,0);
      lcd_2.print("Motor2 is ");
      lcd_2.setCursor(0,1);
      lcd_2.print("Restarting");

      lcd_3.clear();
      lcd_3.setCursor(0,0);
      lcd_3.print("Motor3 is ");
      lcd_3.setCursor(0,1);
      lcd_3.print("Restarting");
    }
  }
  else
  {
    reset_1 = true;
    reset_2 = true;
    reset_3 = true;

    lcd_1.clear();
    lcd_1.setCursor(0,0);
    lcd_1.print("Motor1 is ");
    lcd_1.setCursor(0,1);
    lcd_1.print("Stopping");
    
    lcd_2.clear();
    lcd_2.setCursor(0,0);
    lcd_2.print("Motor2 is ");
    lcd_2.setCursor(0,1);
    lcd_2.print("Stopping");
    
    lcd_3.clear();
    lcd_3.setCursor(0,0);
    lcd_3.print("Motor3 is ");
    lcd_3.setCursor(0,1);
    lcd_3.print("Stopping");
  }
}