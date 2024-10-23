#include <Wire.h>
#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <BH1750.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

// Pin definitions
const int ledPin = 13;
#define DHTPIN D4      // Pin connected to the DHT22
#define DHTTYPE DHT22  // DHT 22 (AM2302)

// Firebase and Wi-Fi credentials
const char* FIREBASE_HOST = "dhtsensor-3fe69-default-rtdb.firebaseio.com";
const char* FIREBASE_AUTH = "AIzaSyAGLUgcBxrOwy4zeCLmSKewryZamfLKguI";
const char* WIFI_SSID = "B415";
const char* WIFI_PASSWORD = "appletv415";

// Firebase objects
FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;

// Sensor objects
DHT dht(DHTPIN, DHTTYPE);
BH1750 lightMeter;

// NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 25200, 60000);  // 7-hour offset for Thailand (UTC+7)

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  // Start DHT22 sensor
  dht.begin();

  // Start BH1750 sensor
  Wire.begin();
  if (lightMeter.begin()) {
    Serial.println(F("BH1750 ready."));
  } else {
    Serial.println(F("BH1750 error."));
  }

  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected to Wi-Fi");

  // Initialize NTP client
  timeClient.begin();

  // Set up Firebase
  config.host = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;

  // Initialize Firebase with the config and auth objects
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  Serial.println("Connected to Firebase");
}

String getFormattedTime() {
  timeClient.update();
  unsigned long rawTime = timeClient.getEpochTime();
  struct tm *ptm = gmtime((time_t *)&rawTime);

  char buffer[20];
  sprintf(buffer, "%04d-%02d-%02d %02d:%02d:%02d", 
          ptm->tm_year + 1900, ptm->tm_mon + 1, ptm->tm_mday,
          ptm->tm_hour, ptm->tm_min, ptm->tm_sec);

  return String(buffer);
}

void logData(String path, float temp, float humid, float light) {
  String timestamp = getFormattedTime();
  String logPath = path + "/" + timestamp;
  
  // Log temperature
  if (Firebase.setFloat(firebaseData, logPath + "/temp", temp)) {
    Serial.print("Logged Temperature: ");
    Serial.println(temp);
  } else {
    Serial.println("Failed to log temperature");
    Serial.println(firebaseData.errorReason());
  }

  // Log humidity
  if (Firebase.setFloat(firebaseData, logPath + "/humid", humid)) {
    Serial.print("Logged Humidity: ");
    Serial.println(humid);
  } else {
    Serial.println("Failed to log humidity");
    Serial.println(firebaseData.errorReason());
  }

  // Log light level
  if (Firebase.setFloat(firebaseData, logPath + "/light", light)) {
    Serial.print("Logged Light Level: ");
    Serial.println(light);
  } else {
    Serial.println("Failed to log light level");
    Serial.println(firebaseData.errorReason());
  }
}

void loop() {
  // Read DHT22 values
  float temp = dht.readTemperature();
  float humid = dht.readHumidity();

  // Read BH1750 light value
  float light = lightMeter.readLightLevel();

  // Check if readings are valid
  if (isnan(temp) || isnan(humid)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  if (light == -1) {
    Serial.println("Failed to read from BH1750 sensor!");
    return;
  }

  // Turn on the LED and log the data with a timestamp
  digitalWrite(ledPin, HIGH);
  Serial.println("LED is ON");

  String logPath = "/log";
  logData(logPath, temp, humid, light);

  delay(5000);  // Delay between readings

  // Turn off the LED
  digitalWrite(ledPin, LOW);
  Serial.println("LED is OFF");

  delay(5000);  // Delay between readings
}