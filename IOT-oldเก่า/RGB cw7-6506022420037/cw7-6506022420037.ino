// #include <DHT.h>

// const int R = D7;
// const int G = D6;
// const int B = D5;
// const int DHT_PIN = D4;

// #define DHTTYPE DHT22
// DHT dht(DHT_PIN, DHTTYPE);

// void setup() {
//   pinMode(R, OUTPUT);
//   pinMode(G, OUTPUT);
//   pinMode(B, OUTPUT);
//   dht.begin();
  
//   Serial.begin(9600);
// }

// void loop() {
//   float humidity = dht.readHumidity();
  
//   if (isnan(humidity)) {
//     Serial.println("Failed to read from DHT sensor!");
//     return;
//   }
  
//   Serial.print("Humidity: ");
//   Serial.print(humidity);
//   Serial.println("%");
  
//   int r = map(humidity, 0, 100, 0, 255); 
//   int g = 0; 
//   int b = map(humidity, 0, 100, 255, 0); 

//   analogWrite(R, r);
//   analogWrite(G, g);
//   analogWrite(B, b);

//   delay(200);
// }


#include <DHT.h>

const int R = D7;
const int G = D6;
const int B = D5;
const int DHT_PIN = D4;

#define DHTTYPE DHT22
DHT dht(DHT_PIN, DHTTYPE);

void setup() {
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  dht.begin();
  
  Serial.begin(9600);
}

void loop() {
  float humidity = dht.readHumidity();
  
  if (isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println("%");
  
  if (humidity > 70) {
    // ความชื้นมากกว่า 70% -> สีแดง
    analogWrite(R, 255);
    analogWrite(G, 0);
    analogWrite(B, 0);
  } else if (humidity >= 50 && humidity <= 70) {
    analogWrite(R, 0);
    analogWrite(G, 255);
    analogWrite(B, 0);
  } else {
    analogWrite(R, 0);
    analogWrite(G, 0);
    analogWrite(B, 255);
  }

  delay(200);
}
