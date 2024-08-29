const int trigPin = 5;
const int echoPin = 6;

// Define sound velocity in cm/uS
#define SOUND_VELOCITY 0.034
#define CM_TO_INCH 0.393701

long duration = 0;
float distanceCm = 0.0;


void setup() {
  Serial.begin(9600); 
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distanceCm = duration * SOUND_VELOCITY / 2;

  if (distanceCm > 100) {
    distanceCm = 100;
  }



  Serial.print("Distance: ");
  Serial.print(100-distanceCm);
  Serial.println(" cm ");



  delay(1000);
  }
