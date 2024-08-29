#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 16
Adafruit_SSD1306 display(OLED_RESET);

const int analogInPin = A0;   // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9;
int sensorValue = 0;

void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Initialize the OLED display at address 0x3C
  display.clearDisplay(); // Clear the display buffer
  display.setTextSize(1); // Set text size
  display.setTextColor(WHITE);
  display.setCursor(0, 0); // Set cursor position
  display.println(" KMUTNB ");
  display.setCursor(0, 10);
  display.setTextSize(2);
  display.setTextColor(BLACK, WHITE); // Set text color to white on black background
  display.println(" Myarduino");
  display.setCursor(0, 32);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("128 x 64 Pixels 0.96");
  display.setCursor(0, 48);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println(" www.myarduino.net "); // Display the URL
  display.display();
}

void loop() {
  sensorValue = analogRead(analogInPin);
  Serial.print("Analog Input = ");
  Serial.println(sensorValue);

  display.clearDisplay(); // Clear the display buffer
  display.setTextSize(1); // Set text size
  display.setTextColor(WHITE);

  display.setCursor(0, 0); // Set cursor position
  display.println(" Analog Value ");

  display.setCursor(0, 16); // Set cursor position for the analog value
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print("VR ");
  display.println(sensorValue); // Display the "VR" followed by the analog value

  display.display(); // Update the display with the new buffer content

  delay(1000);
}
