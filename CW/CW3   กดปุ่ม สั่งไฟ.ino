const int buttonPin = D7;   
const int ledG = D4;        
const int ledY = D5;        
const int ledR = D6;       

int buttonState = 0;       
int lastButtonState = 0;  
int buttonPressCount = 0;  

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

  if (buttonState == LOW && lastButtonState == HIGH) {
    buttonPressCount++;
    Serial.print("Button pressed ");
    Serial.print(buttonPressCount);
    Serial.println(" times.");

    if (buttonPressCount == 10) {
      digitalWrite(ledG, HIGH);
      digitalWrite(ledY, LOW);
      digitalWrite(ledR, LOW);
    } else if (buttonPressCount == 20) {
      digitalWrite(ledG, LOW);
      digitalWrite(ledY, HIGH);
      digitalWrite(ledR, LOW);
    } else if (buttonPressCount == 30) {
      digitalWrite(ledG, LOW);
      digitalWrite(ledY, LOW);
      digitalWrite(ledR, HIGH);  
    } else if (buttonPressCount == 40) {
      digitalWrite(ledG, HIGH);
      digitalWrite(ledY, HIGH);
      digitalWrite(ledR, HIGH);  
    } else if (buttonPressCount == 41) {
      digitalWrite(ledR, LOW);
      digitalWrite(ledG, LOW);
      digitalWrite(ledY, LOW);
      buttonPressCount = 1 ;
    }
    
  }

  lastButtonState = buttonState;

  delay(50);
}
