
#define BLYNK_TEMPLATE_ID           "TMPL6ZC1T2uSg"
#define BLYNK_TEMPLATE_NAME         "Quickstart Template"
#define BLYNK_AUTH_TOKEN            "bsfo3m8QtkVBOZJh7R6wuv1M9OEoYO86"
#define BLYNK_PRINT Serial


#include <Wire.h>
#include <BH1750.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>



#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

BH1750 lightMeter;

char ssid[] = "B415";
char pass[] = "appletv415";

BlynkTimer timer;

void setup() {
  Serial.begin(9600);
  
  Wire.begin();
  
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.display();
  delay(2000);
  display.clearDisplay();
  
  lightMeter.begin();
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(1000L, sendToBlynk);
  
  Serial.println(F("BH1750 and OLED Test begin"));
}

void loop() {
  Blynk.run();
  timer.run();
  
  float lux = lightMeter.readLightLevel();
  Serial.print("Digital Light Sensor: ");
  Serial.print(lux);
  Serial.println(" lx");
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.print("Light: ");
  display.print(lux);
  display.println(" lx");
  display.display();
  
  delay(1000);
}

void sendToBlynk() {
  float lux = lightMeter.readLightLevel();
  Serial.print("Sending to Blynk: ");
  Serial.println(lux);
  Blynk.virtualWrite(V4, lux);  
} 



