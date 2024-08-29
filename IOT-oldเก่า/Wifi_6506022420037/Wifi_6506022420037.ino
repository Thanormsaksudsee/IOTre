#include <ESP8266WiFi.h>
#include "ThingSpeak.h"
#include <DHT.h>

const char* ssid = "NongBigPenDekNarakMak";
const char* password = "big123456";

WiFiClient client;
unsigned long myChannelNumber = 2614725;
const char* myWriteAPIKey = "KNOZ40RWUZ9R6HF7";

#define DHTPIN D4  
#define DHTTYPE DHT22 

DHT dht(DHTPIN, DHTTYPE);

unsigned long lastTime = 0;
unsigned long timerDelay = 10000; 

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
  dht.begin();
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    if (WiFi.status() != WL_CONNECTED) {
      Serial.print("Attempting to connect");
      while (WiFi.status() != WL_CONNECTED) {
        WiFi.begin(ssid, password);
        delay(5000);
        Serial.print(".");
      }
      Serial.println("\nConnected.");
    }

    float temp = dht.readTemperature();
    float Humid = dht.readHumidity();
    
    if (isnan(temp) || isnan(Humid)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }

    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.print(" °C, Humidity: ");
    Serial.print(Humid);
    Serial.println(" %");

    int num1 = random(10, 90);
    Serial.print("Random Number = ");
    Serial.println(num1);

    ThingSpeak.writeField(myChannelNumber, 1, num1, myWriteAPIKey);
    ThingSpeak.writeField(myChannelNumber, 2, temp, myWriteAPIKey);
    ThingSpeak.writeField(myChannelNumber, 3, Humid, myWriteAPIKey);

    lastTime = millis();
  }
}
