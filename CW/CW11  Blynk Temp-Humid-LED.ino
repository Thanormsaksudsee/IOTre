#define BLYNK_TEMPLATE_ID           "TMPL6ZC1T2uSg"
#define BLYNK_TEMPLATE_NAME         "Quickstart Template"
#define BLYNK_AUTH_TOKEN            "bsfo3m8QtkVBOZJh7R6wuv1M9OEoYO86"
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>  // เพิ่มการอ้างอิงไลบรารี DHT

char ssid[] = "B415";
char pass[] = "appletv415";

BlynkTimer timer;

// Define the GPIO pin for the LED and DHT
int ledPin = D4; 
#define DHTPIN D5
#define DHTTYPE DHT22 // หรือ DHT11 ถ้าใช้ DHT11

DHT dht(DHTPIN, DHTTYPE); // สร้างอ็อบเจกต์ DHT

BLYNK_WRITE(V0)
{
  int value = param.asInt();
  if(value == 1) {
    digitalWrite(ledPin, HIGH);  // เปิดไฟ LED
  } else {
    digitalWrite(ledPin, LOW);   // ปิดไฟ LED
  }
}

BLYNK_CONNECTED()
{
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

void myTimerEvent()
{
  // อ่านค่าอุณหภูมิและความชื้นจาก DHT
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();       

  // ตรวจสอบว่าการอ่านค่าล้มเหลวหรือไม่
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Blynk.virtualWrite(V1, temperature);  
  Blynk.virtualWrite(V2, humidity);     
  Blynk.virtualWrite(V3, millis() / 1000);  
}

void setup()
{
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT); 
  dht.begin();             

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(1000L, myTimerEvent);  
}

void loop()
{
  Blynk.run();
  timer.run();
}
