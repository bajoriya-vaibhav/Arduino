#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  lcd.begin();                     
  lcd.backlight();                 
  lcd.setCursor(0, 0);
}

void loop() {
  // Sample speed and volume values
  int speed = 45;    // Sample speed value (0-60)
  int volume = 7;    // Sample volume value (0-11)

  // Display speed
  lcd.print("Spd:");
  lcd.print("A");
  if (speed < 10) {
    lcd.print(" ");
  }
  lcd.print(speed);

  // Display volume
  lcd.setCursor(0, 1);
  lcd.print("Vol: ");
  if (volume < 10) {
    lcd.print(" ");
  }
  lcd.print(volume);

  // Example for other motors
  // Replace these with your own motor values and display positions
  
  // Motor 2
  int motor2_speed = 30;  // Sample speed value for motor 2 (0-60)
  int motor2_volume = 9;  // Sample volume value for motor 2 (0-11)
  
  lcd.setCursor(8, 0);
  lcd.print("B");
  if (motor2_speed < 10) {
    lcd.print(" ");
  }
  lcd.print(motor2_speed);

  lcd.setCursor(9, 1);
  if (motor2_volume < 10) {
    lcd.print(" ");
  }
  lcd.print(motor2_volume);

  // motor 3
  int motor3_speed = 34;  // Sample speed value for motor 2 (0-60)
  int motor3_volume = 11;  // Sample volume value for motor 2 (0-11)
  
  lcd.setCursor(13, 0);
  lcd.print("C");
  if (motor3_speed < 10) {
    lcd.print(" ");
  }
  lcd.print(motor3_speed);

  lcd.setCursor(14, 1);
  if (motor3_volume < 10) {
    lcd.print(" ");
  }
  lcd.print(motor3_volume);


  delay(1000);  // Delay for demonstration, adjust as needed
}
