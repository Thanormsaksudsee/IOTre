#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 16
Adafruit_SSD1306 display(OLED_RESET);

const int analogInPin = A0; // พินที่เชื่อมต่อกับเซนเซอร์ analog
int sensorValue = 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
}

void loop() {
  sensorValue = analogRead(analogInPin);

  Serial.print("Analog Input = ");
  Serial.println(sensorValue);

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(0, 0);
  display.print("Analog Input = ");
  display.println(sensorValue);

  display.setCursor(0, 16);
  display.setTextSize(2);
  display.setTextColor(WHITE, BLACK); 
  display.println(sensorValue);

  display.display();

  // หน่วงเวลา 1 วินาที
  delay(1);
}