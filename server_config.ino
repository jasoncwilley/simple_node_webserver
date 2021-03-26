// ESP8266 and ESP32 boards are utilezed in the project
// Not all Libs are compatible with both boards
// This if statemtn will allow us to control whether or not to
// import the ESP32 or ESP8266 lib version


#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#elif defined(ESP32)
#include <WiFi.h>
#include <ESPmDNS.h>
#else
#error "Board not found"
#endif


#include "/home/userone/Arduino/simple_node_webserver/index.h"

#include <ESPAsyncWebServer.h>

AsyncWebServer server(80); // server port 80

void notFound(AsyncWebServerRequest *request)
{
  request->send(404", "text/plain", "Are you lost?  The page you requested ws Not Found")
}

void setup(void)   //  Begin setup()
{  
  Serial.begin(115200);  // Begin communiction on Serial 115200
  Serial.println("Creating wifi network");
delay(2000);
// SSID and Password for the ESP32 Access Point
const char* ssid = "smelly_packets";
const char* password = "";  // Access Point is left insecure
  WiFi.softAP(ssid, password);  //Create INSECURE Access Point
  Serial.println("Intializing wifi network");
  delay(2000);
  Serial.println("Access Point configured...");
Serial.println(ssid);     //Return Access Point SSID in Serial
Serial.println("has been created at");
Serial.println(WiFi.softAPIP());  //Return Access Point IP address in Serial

  if (MDNS.begin("ESP")) { //home.local/
    Serial.println("MDNS responder started");
  }




  server.on("/", [](AsyncWebServerRequest * request) // Webserver created at home.local return helo world
  {
    
   String index = INDEX_page;   // Reads the HTML code from defined in index.h
  request->send(200, "text/html", index); //  Displays code from index.h
  });

   server.on("/page1", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
   String message = "Hello world, we meet again...";
  request->send(200, "text/plain", message);
  });

  server.onNotFound(notFound);  // run notFound function if GET returns 404

  server.begin();  // starts webserver
}    //  End setup()


void loop(void)
{
}
