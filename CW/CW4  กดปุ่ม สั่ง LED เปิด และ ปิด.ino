const int buttonPin = D7; 
const int ledG = D4;     
const int ledY = D5;        
const int ledR = D6;      

int buttonState = 0;        
int buttonState2 = 1;    
bool LedOn = false;       

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledY, OUTPUT);
  pinMode(ledR, OUTPUT);

  digitalWrite(ledG, LOW);
  digitalWrite(ledY, LOW);
  digitalWrite(ledR, LOW);

  Serial.begin(9600);
}

void loop() {
  buttonState = digitalRead(buttonPin);

  if (buttonState == LOW && buttonState2 == HIGH) {
    LedOn = !LedOn;

    if (LedOn) {
      digitalWrite(ledG, HIGH);
      digitalWrite(ledY, HIGH);
      digitalWrite(ledR, HIGH);
      Serial.println("LEDs ON");
    } 
    if (!LedOn) {
      digitalWrite(ledG, LOW);
      digitalWrite(ledY, LOW);
      digitalWrite(ledR, LOW);
      Serial.println("LEDs OFF");
    }
  }

  buttonState2 = buttonState;

  delay(50); 
}
