#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include <ESPmDNS.h>

const char* ssid = "SKYPEMHG";
const char* password = "8NHetSWQAJ75";
#define HOSTNAME "ESP32Test" //use http://ESP32Test to access OTA update
AsyncWebServer server(80);

void setup(void) {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
  WiFi.setHostname(HOSTNAME); //define hostname
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Update firmware via http://");  
  Serial.println(WiFi.getHostname());

  // load OTA page automatically
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/html",
      "<script type='text/javascript'>"
      "window.location.href = '/update'"
      "</script>"   );
  });

  if(!MDNS.begin(HOSTNAME)) {  
     Serial.println("Error starting mDNS");
     return;
  }
  
  AsyncElegantOTA.begin(&server);    // Start ElegantOTA
  server.begin();
  Serial.println("HTTP server started.");
}

void loop(void) {
 
}
