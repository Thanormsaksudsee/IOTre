#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

// Uncomment one of the lines below for the DHT sensor type you're using!
#define DHTTYPE DHT22 // DHT 22 (AM2302), AM2321
// #define DHTTYPE DHT11
// #define DHTTYPE DHT21 // DHT 21 (AM2301)

// Wi-Fi and MQTT server credentials
const char* ssid = "TUTOR-6";
const char* password = "ilovelibrary";
const char* mqtt_server = "broker.hivemq.com";
const char* mqttport = "1883";

// MQTT broker credentials (set to NULL if not required)
const char* MQTT_username = NULL;
const char* MQTT_password = NULL;

// Initialize WiFi and MQTT clients
WiFiClient espClient;
PubSubClient client(espClient);

// GPIO pins for DHT sensor and led (LED)
const int DHTPin = D4;  // GPIO 5 = D1 on ESP-12E NodeMCU board
const int led = D6;    // GPIO 4 = D2 on ESP-12E NodeMCU board

// Initialize DHT sensor
DHT dht(DHTPin, DHTTYPE);

// Timing variables
long now = millis();
long lastMeasure = 0;

// Function to connect to Wi-Fi
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("WiFi connected - ESP IP address: ");
  Serial.println(WiFi.localIP());
}

// MQTT callback function to handle received messages
void callback(String topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
 
  String messageTemp;
  for (int i = 0; i < length; i++) {
    messageTemp += (char)message[i];
  }
  Serial.println(messageTemp);

  // Control the led (LED) based on the received message
  if (topic == "big/led") {
    Serial.print("Changing Room led to ");
   
    if (messageTemp == "on") {
      digitalWrite(led, HIGH);
      Serial.println("On");
    } else if (messageTemp == "off") {
      digitalWrite(led, LOW);
      Serial.println("Off");
    }
  }
}

// Function to reconnect to the MQTT broker and resubscribe to topics
void reconnect() {
  while (!client.connected()) {
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX); // Create a random client ID
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect with client ID
    if (client.connect(clientId.c_str(), MQTT_username, MQTT_password)) {
      Serial.println("connected");
      // Subscribe to the topic
      client.subscribe("big/led");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

// Setup function to initialize GPIOs, start serial communication, and configure MQTT
void setup() {
  pinMode(led, OUTPUT);
  dht.begin();
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, atoi(mqttport)); // Use mqttport variable
  client.setCallback(callback);
}

// Main loop to keep the ESP8266 connected to the MQTT broker and publish sensor data
void loop() {
  if (!client.connected()) {
    reconnect();
  }
 
  client.loop();
 
  now = millis();
 
  // Publish temperature and humidity every 5 seconds
  if (now - lastMeasure > 5000) {
    lastMeasure = now;
   
    float humidity = dht.readHumidity();
    float temperatureC = dht.readTemperature();       // Celsius
    float temperatureF = dht.readTemperature(true);   // Fahrenheit

    if (isnan(humidity) || isnan(temperatureC) || isnan(temperatureF)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }

    // Publish sensor data
    client.publish("big/temperature", String(temperatureC).c_str());
    client.publish("big/humidity", String(humidity).c_str());
   
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
    Serial.print("Temperature: ");
    Serial.print(temperatureC);
    Serial.println(" °C");
    Serial.print("Temperature: ");
    Serial.print(temperatureF);
    Serial.println(" °F");
  }
}