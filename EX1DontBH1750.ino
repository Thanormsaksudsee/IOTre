#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>
#define SOUND_VELOCITY 0.034
#define CM_TO_INCH 0.393701
#define WARMLIGHT_PIN 6   // Yellow LED for warming light
#define FAN_PIN 7         // Green LED for fan
#define DHTPIN 8          // Pin for DHT22 sensor
#define DHTTYPE DHT22     // Define the sensor type
const int trigPin = 9;
const int echoPin = 10;
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1     // Reset pin for OLED


const int R = A1;
const int G = A2;
const int B = A3;

DHT dht(DHTPIN, DHTTYPE);

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);



long duration = 0;
float distanceCm = 0.0;

void setup() {
  Serial.begin(9600);
  
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  
  lightMeter.begin();
  dht.begin();
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(WARMLIGHT_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * SOUND_VELOCITY / 2;
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Temp: ");
  display.print(t);
  display.print(" C");

  display.setCursor(0, 16);
  display.print("Humidity: ");
  display.print(h);
  display.print(" %");

  display.setCursor(0, 32);
  display.print("Food Level: ");
  display.print(100-distanceCm);
  display.print("cm");

  display.display();

  if (distanceCm > 100) {
    distanceCm = 100;
  }

  if (t >= 26.33) {
    analogWrite(R, 255);  // Set RGB LED to red
    analogWrite(G, 0);
    analogWrite(B, 0);
  }  
  if (h >= 65) {
    analogWrite(R, 0);
    analogWrite(G, 255);  // Set RGB LED to green
    analogWrite(B, 0);
  } 
  if (distanceCm > 90) {
    analogWrite(R, 0);
    analogWrite(G, 0);  // Set RGB LED to white
    analogWrite(B, 255);
  }
  else {
    analogWrite(R, 0);
    analogWrite(G, 0);
    analogWrite(B, 0);    // Turn off the RGB LED
  }

  Serial.print("Distance: ");
  Serial.print(100-distanceCm);
  Serial.println(" cm ");
  
  if (t < 20) {   
    digitalWrite(WARMLIGHT_PIN, HIGH);   
    digitalWrite(FAN_PIN, LOW);         
  } else if (t > 30) {  
    digitalWrite(FAN_PIN, HIGH);         
    digitalWrite(WARMLIGHT_PIN, LOW);  
  } else {
    digitalWrite(WARMLIGHT_PIN, LOW);   
    digitalWrite(FAN_PIN, LOW);         
  }
  delay(1000);  
}