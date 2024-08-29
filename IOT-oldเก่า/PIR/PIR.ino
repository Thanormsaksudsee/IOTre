// กำหนดพินสำหรับ PIR และ LED
#define PIR_PIN D5   // พินที่เชื่อมต่อกับ OUT ของเซ็นเซอร์ PIR
#define LED_PIN D7   // พินที่เชื่อมต่อกับ LED

int pirValue=0;
int motionDetected = 0;
void getPirValue(void);
void setup()

{
  Serial.begin(115200);
  delay(10);
  pinMode(LED_PIN, OUTPUT);
  pinMode(PIR_PIN, INPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop()
{
  getPirValue();
}


void getPirValue(void)

{
  pirValue = digitalRead(PIR_PIN);
  if (pirValue)
  {
    Serial.println(pirValue);
    // Serial.println("==> Motion detected");

  }
  digitalWrite(LED_PIN, PIR_PIN);
}
