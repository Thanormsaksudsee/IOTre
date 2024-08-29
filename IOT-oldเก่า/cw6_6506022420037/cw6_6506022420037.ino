#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED display configuration
#define OLED_RESET 16
Adafruit_SSD1306 display(OLED_RESET);

// Ultrasonic sensor pins
const int trigPin = D5;
const int echoPin = D6;

// Define sound velocity in cm/uS
#define SOUND_VELOCITY 0.034
#define CM_TO_INCH 0.393701

// Variables to store distance values
long duration = 0;
float distanceCm = 0.0;
float distanceInch = 0.0;
int distanceFeet = 0;
int distanceInchRemainder = 0;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Stop execution if OLED allocation fails
  }
  display.clearDisplay();
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  
  distanceCm = duration * SOUND_VELOCITY / 2;
  
  if (distanceCm > 200) {
    distanceCm = 200;
  }
  
  distanceInch = (200-distanceCm) * CM_TO_INCH;
  distanceFeet = (int)distanceInch / 12;
  distanceInchRemainder = distanceInch - (distanceFeet * 12);
  
  Serial.print("Distance: ");
  Serial.print(200-distanceCm);
  Serial.print(" cm ");
  Serial.print(distanceFeet);
  Serial.print(" ft ");
  Serial.print(distanceInchRemainder);
  Serial.println(" inch");
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Distance: ");
  display.print(200-distanceCm);
  display.println(" cm");

  // display.setCursor(0, 16);
  // display.setTextSize(1);
  // display.print(distanceFeet);
  // display.print(" ft ");
  // display.print(distanceInchRemainder);
  // display.println(" inch");

  display.display();

  delay(5); 
}
