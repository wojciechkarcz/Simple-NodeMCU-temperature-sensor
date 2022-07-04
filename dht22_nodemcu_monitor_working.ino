#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "DHTesp.h"


DHTesp dht;


ESP8266WebServer server(80);
long randNumber;
long x;

void setup() {
  Serial.begin(115200);
  dht.setup(5, DHTesp::DHT22);
  
  WiFi.begin("HUAWEI-B535", "GRODEK0507");  

  while (WiFi.status() != WL_CONNECTED) {  

    delay(2000);
    Serial.println("Waiting to connect …");
    }

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());                        

  server.on("/python", handlePath);
  server.on("/led", handleLed);
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


void handlePath() { 

  randNumber = random(1000);
  String newrandom = String(randNumber);
  delay(3000);

  server.send(200, "text/plain", newrandom);

  Serial.println(newrandom);
}

void handleLed() {
  String message = "";

  if (server.arg("time")==""){     

  message = "Temperature Argument not found";

  } else {
       
  x = server.arg("time").toInt();
  
  digitalWrite(LED_BUILTIN, LOW);   
  delay(x);                      
  digitalWrite(LED_BUILTIN, HIGH);

   server.send(200, "text/plain", "LED blinking");
}
}
