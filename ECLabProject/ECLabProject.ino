#include <NewPing.h>
#include <Servo.h>
#include <IRremote.h>

// for the moisture sensor
#define Wet 875
#define sensorPower 13
#define sensorPin A0
int p=12;

// for servo motor
#define SERVO_PIN 11
#define SERVO_PIN2 10

// for metal sensor
const int metalDetectorPin = 9;


// // for the ultra-sonic sensor
// #define TRIGGER_PIN  11
// #define ECHO_PIN 10 
// #define MAX_DISTANCE 200 

// // rc motor pin
// #define DCMOTOR_PIN 8
// #define DCMOTOR_PIN2 7

// servo object instance
Servo servoRotation;  // create a servo object to control a servo motor

Servo servoTilt;

// for the ir sensor
const int IR_PIN_Wet = 8;
const int IR_PIN_Metal = 7;
const int IR_PIN_Dry = 6;  // define the digital pin for the IR sensor
// IRrecv irrecv1(IR_PIN_Wet);
// IRrecv irrecv2(IR_PIN_Dry);
// IRrecv irrecv3(IR_PIN_Metal);

// flag to mark the container which is full
int containerFullWet = 0;
int containerFullDry = 0;
int containerFullMetal = 0;

// // NewPing class for the ultrasonic sensor
// NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);


void setup() {
  pinMode(metalDetectorPin, INPUT);

  servoRotation.attach(SERVO_PIN);  // attaches the servo on pin 11
  servoTilt.attach(SERVO_PIN2);
  servoRotation.write(0);  // sets the servo position to 0 degrees to denote the untilted platform


// for the moisture sensor
  pinMode(sensorPower, OUTPUT);
	pinMode(p,OUTPUT);
	// Initially keep the sensor OFF
	digitalWrite(sensorPower, LOW);

  // for ir sensor
  pinMode(IR_PIN_Wet, INPUT);
  pinMode(IR_PIN_Dry, INPUT);
  pinMode(IR_PIN_Metal, INPUT);

  Serial.begin(9600);  // initialize serial communication
}

void loop() {

  // for the metal sensor
  int metalStatus = digitalRead(metalDetectorPin);

  // for the moisture sensor
	int moisture = MoistureSensor();
  analogWrite(p,0);

  Separator(moisture,metalStatus);

  int containerFullWet = digitalRead(IR_PIN_Wet);
  int containerFullDry = digitalRead(IR_PIN_Dry);
  int containerFullMetal = digitalRead(IR_PIN_Metal);
   
  // unsigned int distance = sonar.ping_cm();  // get the distance in centimeters

  // if (distance <=25) {
  //   openLid(1);
  // }

  messageForFullContainer(containerFullWet,containerFullDry,containerFullMetal);
	
  delay(1000);

  // // for servo motor
  // servoRotation.write(90);  // sets the servo position to 90 degrees 
}


void messageForFullContainer(int containerFullWet,int containerFullDry,int containerFullMetal ){
  if(containerFullWet){
    Serial.println("Wet container is full");
  }
  else if(containerFullDry){
    Serial.println("Dry container is full");
  }
  if(containerFullMetal){
    Serial.println("Metal container is full");
  }
}

//  This function returns the analog moisture measurement
int MoistureSensor() {
	digitalWrite(sensorPower, HIGH);	// Turn the sensor ON
	delay(500);							// Allow power to settle
	int val = analogRead(sensorPin);	// Read the analog value from sensor
	// digitalWrite(sensorPower, LOW);		// Turn the sensor OFF

  Serial.print("Analog Output: ");
  Serial.println(val);
  return val;							// Return analog moisture value
}

// void openLid(int someone){
//   if(someone){
//     Serial.println("Lid is opening");
//   }
// }

// // for servomotor rotation
void rotateMotor(int duration,byte flag) {
  // Set the motor to rotate in one direction
  if(flag){
    for(int i=60;i<120;i++){
      servoRotation.write(i);  // sets the servo position to 120 degrees
    }
    delay(1000); 
    for(int i=120;i>60;i--){
      servoRotation.write(i);  // sets the servo position to 120 degrees
    }         // sets the servo position to 0 degrees
    delay(1000);        // waits for a second
  }
  else{
    for(int i=60;i>0;i--){
      servoRotation.write(i);  // sets the servo position to 120 degrees
    }
    delay(1000); 
    for(int i=0;i<60;i++){
      servoRotation.write(i);  // sets the servo position to 120 degrees
    }         // sets the servo position to 0 degrees
    delay(1000); 
  }

}

void tilt(){
  for(int i=60;i<120;i++){
    servoRotation.write(i);  // sets the servo position to 120 degrees
  }
  
}

void Separator(int moisture,int metal){
  // Serial.println(moisture);
  if(metal){
    Serial.println("Status: Metal Waste");
    rotateMotor(1000,0);
    return ;
  }

  // Determine status of our waste
	if (moisture < Wet) {
		Serial.println("Status: Wet Waste");
    rotateMotor(1000,1);
	} else {
		Serial.println("Status:Dry Waste");
	}
}

