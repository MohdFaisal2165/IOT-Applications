 #include <DHT.h>  
 #include <ESP8266WiFi.h>  
 #include <WiFiClient.h>  
 #include <ThingSpeak.h>
   
 #define DHTPIN D4  
 #define DHTTYPE DHT11  
 DHT dht(DHTPIN, DHTTYPE);
   
 const char* ssid = "Your SSID";  // SSID
 const char* password = "Your Password";  // Password
 WiFiClient client;  
 unsigned long myChannelNumber = 306318; // Change this with your Channel ID 
 const char * myWriteAPIKey = "1ADWPT72U8W5Y7K5";  // Change this with your API key
 uint8_t temperature, humidity;  
 void setup()  
 {  
  Serial.begin(115200);  
  dht.begin();  
  delay(10);  
  // Connect to WiFi network  
  Serial.println();  
  Serial.println();  
  Serial.print("Connecting to ");  
  Serial.println(ssid);  
  WiFi.begin(ssid, password);  
  while (WiFi.status() != WL_CONNECTED)  
  {  
   delay(500);  
   Serial.print(".");  
  }  
  Serial.println("");  
  Serial.println("WiFi connected");  
  // Print the IP address  
  Serial.println(WiFi.localIP());  
  ThingSpeak.begin(client);  
 }  
 void loop()   
 {  
  static boolean data_state = false;  
  temperature = dht.readTemperature();  
  humidity = dht.readHumidity();  
  Serial.print("Temperature Value is :");  
  Serial.print(temperature);  
  Serial.println("C");  
  Serial.print("Humidity Value is :");  
  Serial.print(humidity);  
  Serial.println("%");  
  // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different  
  // pieces of information in a channel. Here, we write to field 1.  
  if( data_state )  
  {  
   ThingSpeak.writeField(myChannelNumber, 1, temperature, myWriteAPIKey);  
   data_state = false;  
  }  
  else  
  {  
   ThingSpeak.writeField(myChannelNumber, 2, humidity, myWriteAPIKey);  
   data_state = true;  
  }  
  delay(300);
 }  
