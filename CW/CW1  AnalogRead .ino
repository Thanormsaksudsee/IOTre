const int analogInPin = A0;   // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9;   // Analog output pin that the LED is attached to
const int ledPin = D4;        // Assuming D4 is your LED pin

int sensorValue = 0;           // Value read from the potentiometer
int outputValue = 0;           // Value output to the PWM (analog out)

void setup() {
  // Initialize serial communications at 9600 bps
  Serial.begin(9600);
  
  // Set the LED pin mode to OUTPUT
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Read the analog input value
  sensorValue = analogRead(analogInPin);

  // Print the analog input value to the serial monitor
  Serial.print("Analog Input = ");
  Serial.println(sensorValue);

  // Check if sensorValue is greater than 500
  if (sensorValue > 500) {
    digitalWrite(ledPin, HIGH);  // Turn the LED on (HIGH is the voltage level)
  } else {
    digitalWrite(ledPin, LOW);   // Turn the LED off by making the voltage LOW
  }
  
  // Delay for 1 second
  delay(1000);
}
