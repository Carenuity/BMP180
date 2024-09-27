#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <SFE_MicroOLED.h> // Include the SFE_MicroOLED library

#define PIN_RESET 255 // Use 255 for I2C (no reset pin)
#define DC_JUMPER 0 // I2C Address: 0 - 0x3C, 1 - 0x3D

MicroOLED oled(PIN_RESET, DC_JUMPER); // Example I2C declaration
Adafruit_BMP085 bmp;

void setup() {
  Serial.begin(9600);

  // Initialize BMP180 sensor
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP180 sensor, check wiring!");
    while (1) {}
  }

  // Initialize OLED display
  oled.begin();
  oled.clear(ALL); // Clear the display's memory (gets rid of artifacts)
  oled.display();
}

void loop() {
  // Wait a few seconds between measurements
  delay(2000);

  // Clear the display's current page
  oled.clear(PAGE);

  // Display pressure
  oled.setFontType(0); // Set font type 0, please see declaration in SFE_MicroOLED.cpp
  oled.setCursor(1, 0);
  oled.print("Pressure: ");
  oled.setCursor(1, 13);
  oled.print(bmp.readPressure());
  oled.print(" Pa");

  // Display temperature
  oled.setCursor(0, 25);
  oled.print("Temperature:");
  oled.setCursor(10, 40);
  oled.print(bmp.readTemperature());
  oled.print(" C");

  // Update the display
  oled.display();

  // Wait before the next update
  delay(2000);
}
