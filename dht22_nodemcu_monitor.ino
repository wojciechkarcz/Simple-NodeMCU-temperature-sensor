#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "DHTesp.h"

DHTesp dht;

#Define pin number of NodeMcu with connected DHT22 sensor
int dhtPin = 5; 

ESP8266WebServer server(80);
long randNumber;
long x;

void setup() {
  Serial.begin(115200);
  dht.setup(dhtPin, DHTesp::DHT22);
  
  #Change your wifi ssid and password
  WiFi.begin("Your WiFi SSID", "Your WiFi password");  

  while (WiFi.status() != WL_CONNECTED) {  

    delay(2000);
    Serial.println("Waiting to connect …");
    }

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());                        

  server.on("/temp", handleTemp);
   
  server.begin();                                                   
  Serial.println("Server listening");
}

void loop() {
  server.handleClient(); 
}

void handleTemp() {
  float h = dht.getHumidity();
  float t = dht.getTemperature();
  Serial.println(h);
  Serial.println(t);
  Serial.println("");
  //delay(2000);
  String temperature = String(t);
  String humidity = String(h);
  String message = temperature + "&"+ humidity;
  server.send(200, "text/plain", message);
  Serial.print("Temperature send: ");
  Serial.println(temperature);
  Serial.println("");
}



