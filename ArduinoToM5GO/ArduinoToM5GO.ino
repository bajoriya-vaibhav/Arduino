
// #include <SoftwareSerial.h>

// SoftwareSerial mySerial(0, 1); // RX, TX

// void setup() {
//   Serial.begin(9600);
//   mySerial.begin(9600);
// }

// void loop() {
//   String Data = "1";
//   mySerial.println(Data);

//   delay(1000);
// }


void setup() {
  Serial.begin(9600); // Set the baud rate to 9600 (make sure it matches the M5GO baud rate)
}

void loop() {
  // Send a string over serial
  Serial.println("Hello from Arduino!");

  delay(1000); // Adjust the delay based on your requirements
}

