#include <vector>
#include "AsyncTCP.h"
#include "ESPAsyncWebServer.h"
#include "ESPAsyncTunnel.h"
#include "ArduinoJson.h"


// WIFI
const String ssid = "your ssid";
const String password = "password";

// Web Server & Sevices
AsyncWebServer server(80);
char* indexPath = "/esp32_radio/vue-radio/dist/index.html";


void setupWifi() {
  Serial.begin(115200);
  //WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(), password.c_str());

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
}

void setupServer() {
  // rewrites
  server.rewrite( "/", indexPath) ;
  server.rewrite( "/index.html", indexPath);
  server.rewrite( "/favicon.ico", "/esp32_radio/vue-radio/dist/favicon.ico");
  
  // tunnel the index.html request 
  server.on(indexPath, HTTP_GET, [&](AsyncWebServerRequest *request){
      ClientRequestTunnel tunnel; 
      if (tunnel.open("https://pschatzmann.github.io", request->url())) {
          String result = tunnel.getString();
          request->send(200, "text/html", result);          
      } else {
          request->send(tunnel.getHttpCode());
      }
  });

  server.on("/esp32_radio/*", HTTP_GET, [&](AsyncWebServerRequest *request){
    String moved_url = "https://pschatzmann.github.io"+request->url();
    request->redirect(moved_url);
  });

  // Generic Services
  server.on("/service/info", HTTP_GET, [](AsyncWebServerRequest *request){
      AsyncResponseStream *response = request->beginResponseStream("application/json");
      StaticJsonDocument<200> doc;
      doc["heap"] = ESP.getFreeHeap();
      doc["ssid"] = WiFi.SSID();
      serializeJson(doc, *response);
      request->send(response);
  });

  //Shut down server
  server.on("/service/shutdown", HTTP_POST, [](AsyncWebServerRequest *request){
      esp_deep_sleep_start();
  });

  server.on("/service/play", HTTP_POST, [](AsyncWebServerRequest *request){
      esp_deep_sleep_start();
  });

  // start server
  server.begin();
}


void setup(){  
  setupWifi();
  setupServer();

  Serial.println();
  Serial.print("You can connect to ");
  Serial.println(WiFi.localIP());  
}


void loop(){
}
