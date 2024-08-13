#include <M5Stack.h>
#include <WiFi.h>

#define WIFI_NETWORK "Homeless"
#define WIFI_PASS "sherlock"
#define WIFI_TIMEOUT 20000

WiFiServer server(80);

// void setup() {
//   M5.begin();
//   M5.Power.begin();
//   M5.Lcd.setTextSize(3);

//   unsigned long start = millis();

//   Serial.begin(115200);
 
//   WiFi.begin(WIFI_NETWORK, WIFI_PASS);
 
//   while (WiFi.status() != WL_CONNECTED && millis() - start < WIFI_TIMEOUT) {
//     delay(500);
//     Serial.println("Connecting to WiFi..");
    
//   }
//   M5.Lcd.println(WiFi.status());
//   if(WiFi.status() != WL_CONNECTED){
//     Serial.println("Failed to connect");
//   }
//   else{
//     Serial.println("Connected to the WiFi network");
//     Serial.println("");
//     Serial.println("WiFi connected.");
//     Serial.println("IP address: ");
//     Serial.println(WiFi.localIP()); //show ip address when connected on serial monitor.
//   }
// }
 
// void loop() {
//   WiFiClient client = server.available();

//   if (client) {
//     Serial.println("New client connected");

//     while (client.connected()) {
//       if (client.available()) {
//         char c = client.read();
//         Serial.write(c); // Print received data to M5GO Serial Monitor
//         M5.Lcd.println(c);
//       }
//     }

//     Serial.println("Client disconnected");
//   }
// }

void setup() {
  M5.begin();
  M5.Power.begin();
  M5.Lcd.setTextSize(3);

  // Connect to Wi-Fi
  WiFi.begin(WIFI_NETWORK, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  Serial.println("Connected to the WiFi network");
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); 

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New client connected");
    String data = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (c == '\n') {
          Serial.println(data);
          M5.Lcd.println(data);
          data = ""; 
        } else {
          data += c;
        }
      }
    }

    Serial.println("Client disconnected");
    delay(1000); 
  }
}

// void setup()
// {
//   M5.begin();
//   M5.Power.begin();
//   M5.Lcd.setTextSize(3);
//   Serial2.begin(9600);
// }

// void loop() {   
// if (Serial2.available() > 0) 
// {
//   String data = Serial.readStringUntil('\n');
//   Serial.println(data);
//   M5.Lcd.println(data);
// }
// }