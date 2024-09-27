#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <U8g2lib.h>

// Declaration for SSD1306 display connected using I2C
#define SCREEN_ADDRESS 0x3C
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

Adafruit_BMP085 bmp;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP085/BMP180 sensor, check wiring!");
    while (1) {}
  } 
  
  // Initialize the OLED object
  u8g2.begin();
  
  // Set a cool font (choose from options below)
   u8g2.setFont(u8g2_font_ncenB08_tr);  // Nice serif font, size 8
  // u8g2.setFont(u8g2_font_fur20_tn);   // Futuristic, size 20 (works for bigger text)
  // u8g2.setFont(u8g2_font_helvR10_tf);  // Helvetica-like font, size 10 (similar to Arial)
  //u8g2.setFont(u8g2_font_t0_12_tr);    // Pixel font, size 12 (looks retro)
}

void loop() {
  // Initialize by clearing the display.
  u8g2.clearBuffer();
  
  // Display temperature
  u8g2.setCursor(31, 25);  // Set cursor position
  u8g2.print("Temperature:");
  u8g2.setCursor(35, 38);  // Set cursor position
  u8g2.print(bmp.readTemperature());
  u8g2.print("C");
  
  // Display pressure
  u8g2.setCursor(32, 48);
  u8g2.print("Pressure:");
  
  // Convert pressure to a string
  float pressure = bmp.readPressure() / 100.0; // Convert Pa to hPa
  char pressureStr[10];
  dtostrf(pressure, 6, 2, pressureStr); // Convert float to string with 2 decimal places
   u8g2.setCursor(33, 58);
  u8g2.print(pressureStr);
  u8g2.print(" hPa");

  // Output pressure to Serial Monitor
  Serial.print(pressureStr);
  Serial.println(" hPa");

  // Send buffer to the display
  u8g2.sendBuffer();
  
  delay(3000);
}
