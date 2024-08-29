#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

const char* ssid = "NongBigPenDekNarakMak";
const char* password = "big123456";

WiFiClient client;

unsigned long myChannelNumber = 2614725;
const char * myWriteAPIKey = "KNOZ40RWUZ9R6HF7";

unsigned long lastTime = 0;
unsigned long timerDelay = 1000;

//float temperatureC;

int num1;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);

}

void loop() {
  // put your main code here, to run repeatedly:
  if ((millis() - lastTime) > timerDelay) {
    if(WiFi.status() != WL_CONNECTED) {
      Serial.print("Attempting to connect");
      while(WiFi.status() != WL_CONNECTED) {
        WiFi.begin(ssid, password);
        delay(5000);
      }
      Serial.print("/nConnected.");
    }
    lastTime = millis();
  }

}