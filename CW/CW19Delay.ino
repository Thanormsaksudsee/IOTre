// Define the relay pins
int relay1 = D1;  // Relay channel 1
int relay2 = D2;  // Relay channel 2
int relay3 = D3; // Relay channel 3
int relay4 = D4; // Relay channel 4

void setup() {
  // Initialize the relay pins as outputs
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  
  // Ensure all relays are turned off initially
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
  
  delay(1000); // delay for 1 second
}

void loop() {
  // Turn on Relay 1 (LED 1 ON)
  digitalWrite(relay1, HIGH);
  delay(3000); // keep LED 1 on for 3 seconds
  digitalWrite(relay1, LOW); // Turn off Relay 1 (LED 1 OFF)
  
  // Turn on Relay 2 (LED 2 ON)
  digitalWrite(relay2, HIGH);
  delay(3000); // keep LED 2 on for 3 seconds
  digitalWrite(relay2, LOW); // Turn off Relay 2 (LED 2 OFF)
  
  // Turn on Relay 3 (LED 3 ON)
  digitalWrite(relay3, HIGH);
  delay(3000); // keep LED 3 on for 3 seconds
  digitalWrite(relay3, LOW); // Turn off Relay 3 (LED 3 OFF)
  
  // Turn on Relay 4 (LED 4 ON)
  digitalWrite(relay4, HIGH);
  delay(3000); // keep LED 4 on for 3 seconds
  digitalWrite(relay4, LOW); // Turn off Relay 4 (LED 4 OFF)
}
