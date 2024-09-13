#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include "DHT.h"

// Define DHT type and pin
#define DHTTYPE DHT22 // DHT 11
const int DHTPin = D4;
#define ON_Board_LED 2 // On-board LED

// WiFi credentials
const char* ssid = "NongBigPenDekNarakMak"; // Replace with your WiFi SSID
const char* password = "big123456"; // Replace with your WiFi Password

// Google Apps Script settings
const char* host = "script.google.com";
const int httpsPort = 443;
String GAS_ID = "AKfycbx_36MHoDXxMHQl0scpORsIipgEsZCHrZzJ1r2d_joJ3epkqOR-Jg4WyjwjuQUxXLM_"; // Replace with your Google Apps Script ID

// Initialize DHT sensor and WiFiClientSecure
DHT dht(DHTPin, DHTTYPE);
WiFiClientSecure client;

void setup() {
  Serial.begin(115200);
  delay(500);

  dht.begin();
  pinMode(ON_Board_LED, OUTPUT);
  digitalWrite(ON_Board_LED, HIGH); // LED off initially

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    digitalWrite(ON_Board_LED, LOW); // Blink LED to indicate connecting
    delay(250);
    digitalWrite(ON_Board_LED, HIGH);
    delay(250);
  }

  // Connection successful
  digitalWrite(ON_Board_LED, HIGH); // LED on
  Serial.println("");
  Serial.print("Successfully connected to: ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  client.setInsecure(); // Disable SSL certificate validation (not recommended for production)
}

void loop() {
  static long lastMeasure = 0;
  long now = millis();

  // Measure data every 3 seconds
  if (now - lastMeasure > 3000) {
    lastMeasure = now;

    float h = dht.readHumidity();
    float t = dht.readTemperature();
    float f = dht.readTemperature(true);

    if (isnan(h) || isnan(t) || isnan(f)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }

    float hic = dht.computeHeatIndex(t, h, false);
    static char temperatureTemp[7];
    dtostrf(hic, 6, 2, temperatureTemp);

    static char humidityTemp[7];
    dtostrf(h, 6, 2, humidityTemp);

    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %\t Temperature: ");
    Serial.print(t);
    Serial.print(" *C ");
    Serial.print(f);
    Serial.print(" *F\t Heat index: ");
    Serial.print(hic);
    Serial.println(" *C ");

    sendData(t, h);
  }
}

void sendData(float temp, float humi) {
  Serial.println("==========");
  Serial.print("Connecting to ");
  Serial.println(host);

  if (!client.connect(host, httpsPort)) {
    Serial.println("Connection failed");
    return;
  }

  String url = "/macros/s/" + GAS_ID + "/exec?temp=" + String(temp) + "&humi=" + String(humi);
  Serial.print("Requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: ESP8266\r\n" +
               "Connection: close\r\n\r\n");

  Serial.println("Request sent");

  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("Headers received");
      break;
    }
  }

  String line = client.readStringUntil('\n');
  if (line.startsWith("{\"state\":\"success\"")) {
    Serial.println("Data successfully sent to Google Apps Script!");
  } else {
    Serial.println("Failed to send data to Google Apps Script.");
  }

  Serial.print("Reply was: ");
  Serial.println(line);
  Serial.println("Closing connection");
  Serial.println("==========");
  Serial.println();
}
