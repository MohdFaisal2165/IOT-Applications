#include <NewPing.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>  
#include <ThingSpeak.h>  
 
#define TRIGGER_PIN  D6  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     D7  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 600 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

const char* ssid     = "Your SSID"; // SSID
const char* password = "Your Password "; //Password

int sensorvalue=0;
//uint8_t sensorvalue=0;

WiFiClient client;  
unsigned long myChannelNumber = 306318;  // Change it with your Channel ID
const char * myWriteAPIKey = "1ADWPT72U8W5Y7K5"; // Change it with your API key

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  delay(100);
 
  // We start by connecting to a WiFi network
 
  //Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  ThingSpeak.begin(client);  
}

void loop() 
{
  Serial.print("Ping: ");
  sensorvalue=20-sonar.ping_cm();
  Serial.print(sensorvalue); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
  ThingSpeak.writeField(myChannelNumber, 3, sensorvalue, myWriteAPIKey);
  
  delay(3000);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.

}
