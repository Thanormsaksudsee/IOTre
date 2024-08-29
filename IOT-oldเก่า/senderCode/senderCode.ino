#include <ESP8266WiFi.h>
#include <espnow.h>

// Define pin numbers for switches
#define SW1_PIN  D0
#define SW2_PIN  D1
#define SW3_PIN  D2
#define SW4_PIN  D4

// Define the broadcast address of the receiver (Slave)
uint8_t broadcastAddress[] = {0x68, 0xC6, 0x3A, 0xAC, 0x4A, 0xC5};

// Define a structure to hold the switch states
typedef struct struct_message {
  bool SW_1;
  bool SW_2;
  bool SW_3;
  bool SW_4;
} struct_message;

// Create an instance of the structure
struct_message myData;

unsigned long lastTime = 0;
unsigned long timerDelay = 50; // Delay in milliseconds

// Callback function to handle the result of the data sent
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0) {
    Serial.println("Delivery Success");
  } else {
    Serial.println("Delivery Fail");
  }
}

void setup() {
  Serial.begin(115200);

  // Initialize the switch pins as input with internal pull-up resistors
  pinMode(SW1_PIN, INPUT_PULLUP);
  pinMode(SW2_PIN, INPUT_PULLUP);
  pinMode(SW3_PIN, INPUT_PULLUP);
  pinMode(SW4_PIN, INPUT_PULLUP);

  // Set initial switch states
  myData.SW_1 = digitalRead(SW1_PIN) == LOW;  // Switch pressed = LOW
  myData.SW_2 = digitalRead(SW2_PIN) == LOW;
  myData.SW_3 = digitalRead(SW3_PIN) == LOW;
  myData.SW_4 = digitalRead(SW4_PIN) == LOW;

  // Set device as a Wi-Fi station
  WiFi.mode(WIFI_STA);

  // Initialize ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register send callback
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);

  // Register the receiver (peer) with the broadcast address
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}

void loop() {
  // Check if the timer delay has passed
  if ((millis() - lastTime) > timerDelay) {
    // Read switch states
    myData.SW_1 = digitalRead(SW1_PIN) == LOW;  // Switch pressed = LOW
    myData.SW_2 = digitalRead(SW2_PIN) == LOW;
    myData.SW_3 = digitalRead(SW3_PIN) == LOW;
    myData.SW_4 = digitalRead(SW4_PIN) == LOW;

    // Send data to the receiver
    esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));

    // Update the last time the data was sent
    lastTime = millis();
  }
}
