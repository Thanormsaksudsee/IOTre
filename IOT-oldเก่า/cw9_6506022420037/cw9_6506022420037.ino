#include <ESP8266WiFi.h>

const char* ssid = "NongBigPenDekNarakMak";
const char* password = "big123456";
int LED1 = D4;
int LED2 = D5;
int LED3 = D6;
WiFiServer server(80);

void setup()
{
  Serial.begin(115200); // Default Baudrate
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);

  Serial.print("Connecting to the Network");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  server.begin(); // Starts the Server
  Serial.println("Server started");

  Serial.print("IP Address of network: ");
  Serial.println(WiFi.localIP());
  Serial.print("Copy and paste the following URL: http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop()
{
  WiFiClient client = server.available();
  if (!client)
  {
    return;
  }
  Serial.println("New client connected");

  while (!client.available())
  {
    delay(1);
  }

  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  int value1 = LOW;
  int value2 = LOW;
  int value3 = LOW;
  
  if (request.indexOf("/LED1=ON") != -1)
  {
    digitalWrite(LED1, HIGH);
    value1 = HIGH;
  }
  if (request.indexOf("/LED1=OFF") != -1)
  {
    digitalWrite(LED1, LOW); 
    value1 = LOW;
  }
  
  if (request.indexOf("/LED2=ON") != -1)
  {
    digitalWrite(LED2, HIGH);
    value2 = HIGH;
  }
  if (request.indexOf("/LED2=OFF") != -1)
  {
    digitalWrite(LED2, LOW);
    value2 = LOW;
  }
  
  if (request.indexOf("/LED3=ON") != -1)
  {
    digitalWrite(LED3, HIGH);
    value3 = HIGH;
  }
  if (request.indexOf("/LED3=OFF") != -1)
  {
    digitalWrite(LED3, LOW); 
    value3 = LOW;
  }

  // HTTP response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("<style>");
  client.println("body { font-family: Arial, sans-serif; }");
  client.println("h1 { color: #333; }");
  client.println("img { max-width: 100%; height: auto; }");
  client.println("</style>");
  client.println("</head>");
  client.println("<body>");
  
  client.println("<h1>ESP8266 LED Control</h1>");
  client.println("<p>Thanormsak sudsee</p>");
  client.println("<img src=''/>");
  
  client.print("CONTROL LED: <br>");
  
  client.print("LED1: ");
  if (value1 == HIGH)
  {
    client.print("ON");
  }
  else
  {
    client.print("OFF");
  }
  client.println("<br><br>");
  client.println("<a href=\"/LED1=ON\"><button>ON</button></a>");
  client.println("<a href=\"/LED1=OFF\"><button>OFF</button></a><br /><br />");

  client.print("LED2: ");
  if (value2 == HIGH)
  {
    client.print("ON");
  }
  else
  {
    client.print("OFF");
  }
  client.println("<br><br>");
  client.println("<a href=\"/LED2=ON\"><button>ON</button></a>");
  client.println("<a href=\"/LED2=OFF\"><button>OFF</button></a><br /><br />");

  client.print("LED3: ");
  if (value3 == HIGH)
  {
    client.print("ON");
  }
  else
  {
    client.print("OFF");
  }
  client.println("<br><br>");
  client.println("<a href=\"/LED3=ON\"><button>ON</button></a>");
  client.println("<a href=\"/LED3=OFF\"><button>OFF</button></a><br /><br />");
  
  client.println("</body>");
  client.println("</html>");

  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
}