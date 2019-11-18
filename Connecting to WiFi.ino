#include<ESP8266WiFi.h>
#include<WiFiClient.h>

const char* ssid ="Your SSID";
const char* password="Your Password";
WiFiClient client;

void setup() 
{
  Serial.begin(921600);
  delay(100);
  Serial.println();
  Serial.println();
  Serial.println("Connecting to");
  Serial.println(ssid);

  WiFi.begin(ssid,password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.println("IP Address:");
  Serial.println(WiFi.localIP());
}
void loop()
{
}
