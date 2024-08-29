const int ledG = D4;   
const int ledY = D5;    
const int ledR = D6;   
int count = 0;          

void setup() {
  pinMode(ledG, OUTPUT);   
  pinMode(ledY, OUTPUT);  
  pinMode(ledR, OUTPUT);  
}

void loop() {

  digitalWrite(ledG, count == 0 ? HIGH : LOW); 
  digitalWrite(ledY, count == 1 ? HIGH : LOW);  
  digitalWrite(ledR, count == 2 ? HIGH : LOW); 


  delay(count == 0 ? 2000 : count == 1 ? 1000 : 15000);  


  count = (count + 1) % 3;  
}
