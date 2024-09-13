#include <TridentTD_LineNotify.h>
#include <DHT.h>

#define SSID "NongBigPenDekNarakMak"
#define PASSWORD "big123456"
#define LINE_TOKEN "1N4PERoIhnk3dE33EO3Q6T4ZJlTsiPGkKh8e05MH38F"
#define DHTPIN 2          // Pin where the DHT sensor is connected
#define DHTTYPE DHT22     // DHT 22 (AM2302)
#define HUMIDITY_THRESHOLD 90  // Set threshold back to 90%
#define INTERVAL 120000   // 2 minutes in milliseconds

DHT dht(DHTPIN, DHTTYPE);
unsigned long lastNotificationTime = 0;
bool shouldNotify = true;

void setup() {
  Serial.begin(115200);
  WiFi.begin(SSID, PASSWORD);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());

  // Initialize Line Notify
  LINE.setToken(LINE_TOKEN);

  // Initialize DHT sensor
  dht.begin();
}

void loop() {
  delay(2000);  // Reading interval (2 seconds)
  
  float humidity = dht.readHumidity();

  if (isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Check if humidity exceeds threshold
  if (humidity > HUMIDITY_THRESHOLD) {
    unsigned long currentTime = millis();
    
    if (shouldNotify || (currentTime - lastNotificationTime >= INTERVAL)) {
      // Send notification with humidity info and picture
      LINE.notify(String("Humidity Alert: ") + humidity + "%");
      LINE.notifyPicture("https://scontent-bkk1-2.xx.fbcdn.net/v/t39.30808-6/459322110_10159803986051442_8561222759903455576_n.jpg?_nc_cat=107&ccb=1-7&_nc_sid=833d8c&_nc_ohc=TbJJxoujk8UQ7kNvgG-hXzl&_nc_ht=scontent-bkk1-2.xx&oh=00_AYC_k3vLkdWrLA5k8Q9797zW8HmcTeizEKvqCP-aO3ijiA&oe=66E97B9E");
      
      lastNotificationTime = currentTime;
      shouldNotify = false;  // Disable further notifications within 2 minutes
    }
  } else {
    shouldNotify = true;  // Reset notification condition if humidity drops below threshold
  }

  Serial.print("Humidity: ");
  Serial.println(humidity);
}