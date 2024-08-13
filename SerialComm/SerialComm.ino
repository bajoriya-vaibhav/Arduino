// #include <M5Stack.h>

// void setup() {
//     M5.begin();  
//     Serial2.begin(115200, SERIAL_8N1, 16,17);
// }

// void loop() {
//     if (Serial.available()) { 
//         int ch = Serial.read();  
//         Serial2.write(ch);  
//         M5.Lcd.printf("Serial:%d\n",ch);
//     }

//     if (Serial2.available()) {
//         String ch = Serial2.read();
//         Serial.write(ch);
//         M5.Lcd.printf("Serial2:%d\n", ch);
//     }
// }

#include <M5Stack.h>

void setup() {
  M5.begin();
  Serial.begin(9600); // Set the baud rate to 9600 (make sure it matches the Arduino baud rate)
}

void loop() {
  if (Serial.available() > 0) {
    // Read the incoming data
    String receivedData = Serial.readStringUntil('\n');
    
    // Print the received data to the M5GO screen
    M5.Lcd.clear();
    M5.Lcd.setCursor(10, 10);
    M5.Lcd.print("Received: ");
    M5.Lcd.print(receivedData);
  }

  delay(100); // Adjust the delay based on your requirements
}
