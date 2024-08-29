#include <ESP8266WiFi.h>
#include <espnow.h>

#define LED1 D0
#define LED2 D1
#define LED3 D2

#define LED_OFF LOW
#define LED_ON HIGH

typedef struct struct_message {
  bool SW_1;
  bool SW_2;
  bool SW_3;
  bool SW_4;
} struct_message;

struct_message myData;

void OnDataRecv(uint8_t *mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  
  Serial.print("SW 1: ");
  Serial.println(myData.SW_1 ? "ON" : "OFF");
  Serial.print("SW 2: ");
  Serial.println(myData.SW_2 ? "ON" : "OFF");
  
  if (myData.SW_1 && myData.SW_2) {
    digitalWrite(LED1, LED_OFF);
    digitalWrite(LED2, LED_OFF);
    digitalWrite(LED3, LED_ON);
  } else {
    digitalWrite(LED1, myData.SW_1 ? LED_ON : LED_OFF);
    digitalWrite(LED2, myData.SW_2 ? LED_ON : LED_OFF);
    digitalWrite(LED3, LED_OFF);  
  }
}

void setup() {
  Serial.begin(115200);
  
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  digitalWrite(LED1, LED_OFF);
  digitalWrite(LED2, LED_OFF);
  digitalWrite(LED3, LED_OFF);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != 0) {
    Serial.println("ERR ESP-NOW!");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {

}
