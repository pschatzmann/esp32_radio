#include <vector>
#include "AsyncTCP.h"
#include "ESPAsyncWebServer.h"
#include "ESPAsyncTunnel.h"
#include "ArduinoJson.h"
#include "Radio.hpp"


// WIFI
const String ssid = "your ssid";
const String password = "password";

// Web Server & Sevices
AsyncWebServer server(80);
String path = "/esp32_radio/vue-radio/dist";
String pathMatch = "/esp32_radio/*";
String indexPath = path+"/index.html";
String iconPath = path+"/favicon.ico";
String serverPath = "https://pschatzmann.github.io";

// Radio
Radio radio;

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
  server.rewrite( "/", indexPath.c_str()) ;
  server.rewrite( "/index.html", indexPath.c_str());
  server.rewrite( "/favicon.ico", iconPath.c_str());
  
  // tunnel the index.html request 
  server.on(indexPath.c_str(), HTTP_GET, [&](AsyncWebServerRequest *request){
      ClientRequestTunnel tunnel; 
      if (tunnel.open(serverPath.c_str(), request->url())) {
          String result = tunnel.getString();
          request->send(200, "text/html", result);          
      } else {
          request->send(tunnel.getHttpCode());
      }
  });

  server.on(pathMatch.c_str(), HTTP_GET, [&](AsyncWebServerRequest *request){
    String moved_url = serverPath+request->url();
    request->redirect(moved_url);
  });

  // Generic Services
  server.on("/service/info", HTTP_GET, [](AsyncWebServerRequest *request){
      ESP_LOGI("[eisp32_radio]","info");    
      radio.sendResponse(request);
  });

  //Shut down server
  server.on("/service/shutdown", HTTP_POST, [](AsyncWebServerRequest *request){
      ESP_LOGI("[eisp32_radio]","shutdown");    
      esp_deep_sleep_start();
  });

  server.on("/service/bluetooth/start", HTTP_POST, [](AsyncWebServerRequest *request){
      radio.startBluetooth();       
      radio.sendResponse(request);
  });

  server.on("/service/bluetooth/stop", HTTP_POST, [](AsyncWebServerRequest *request){
      radio.stopBluetooth();
      radio.sendResponse(request);
  });


  server.onRequestBody([](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total){
    if (request->url() == "/service/streaming/start") {
        String url = radio.getMusicURL(data, len);        
        radio.startStreaming(url);
        radio.sendResponse(request);
    }
  });


  server.on("/service/streaming/stop", HTTP_POST, [](AsyncWebServerRequest *request){
      radio.stopStreaming();
      radio.sendResponse(request);
  });

  server.on("/service/stop", HTTP_POST, [](AsyncWebServerRequest *request){
    radio.stopStreaming();
    radio.stopBluetooth();
  });

  // start server
  server.begin();
  // automatically start Bluetooth
  //radio.startBluetooth();

}

void setup(){  
  audioLogger = &Serial;
  setupWifi();
  setupServer();

  Serial.println();
  Serial.print("You can connect to ");
  Serial.println(WiFi.localIP());  
}


void loop(){
  radio.loop();
}
