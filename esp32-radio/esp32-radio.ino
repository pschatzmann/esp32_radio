/**
    Copyright 2020 Phil Schatzmann

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <WebServer.h>
#include "ESPAsyncTunnel.h"
#include "ArduinoJson.h"
#include "Radio.hpp"


// WIFI
const String ssid = "your ssid";
const String password = "password";


// Web Server & Sevices
WebServer server(80);
String path = "/esp32_radio/vue-radio/dist";
String pathMatch = "/esp32_radio/";

String indexPath = path+"/index.html";
String iconPath = path+"/favicon.ico";
String serverPath = "https://pschatzmann.github.io";
char moved_url[500];
String indexHtml;

// Radio
Radio radio;

void setupWifi() {
  Serial.begin(115200);
  //WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(), password.c_str());

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // copy wifi
  radio.setup();
}


void setupIndexHtml() {
    ClientRequestTunnel tunnel; 
    if (tunnel.open(serverPath+indexPath)) {
        indexHtml = tunnel.getString();
    } else {
        indexHtml = "<!DOCTYPE html><html><body><h1>Error</h1><p>The ESP32 is not available</p></body></html>";
        ESP_LOGE("[eisp32_radio]","Could not read index.html");    
    }
}

void redirect(const char *url){
    ESP_LOGI("[eisp32_radio]","redirect to %s", url);    
    server.sendHeader("Location", url, true);
    server.send(301, "", "");
}

void setupServer() {

  setupIndexHtml();  

  // tunnel the index.html request: We avoid https because this is consuming too much memory
  // so we get the index.html from a http source
  server.on(indexPath.c_str(), HTTP_GET, [&](){
      radio.recordActivity();
      server.send(200, "text/html", indexHtml);    
  });
  
  server.on("/index.html", HTTP_GET, [&](){
      radio.recordActivity();
      server.send(200, "text/html", indexHtml);    
  });

  server.on("/", HTTP_GET, [&](){
      radio.recordActivity();
      server.send(200, "text/html", indexHtml);    
  });

  // redirect favicon
  server.on( "/favicon.ico", HTTP_GET, [&](){
      radio.recordActivity();
      redirect(iconPath.c_str());    
  });

  // redirect all other request to github
  //server.on(pathMatch, HTTP_GET, [&](){
  server.onNotFound([&](){
    String url = server.uri();
    if (url.startsWith(pathMatch)) {  
      ESP_LOGD("[onNotFound]","-> redirect %s",url.c_str());    
      strcpy(moved_url, serverPath.c_str()),
      strcat(moved_url, url.c_str()),    
      redirect(moved_url);
    } else {
      ESP_LOGD("[onNotFound]","-> not found %s",url.c_str());    
      server.send(404, "", "");    
    }
  });

  // Generic Services
  server.on("/service/info", HTTP_GET, [](){
      ESP_LOGD("[eisp32_radio]","info");    
      radio.recordActivity();
      ESP_LOGD("[eisp32_radio]","info");    
      radio.sendResponse(server);
  });

  server.on("/service/shutdown", HTTP_POST, [](){
      ESP_LOGI("[eisp32_radio]","shutdown");    
      radio.recordActivity();
      ESP_LOGI("[eisp32_radio]","shutdown");    
      esp_deep_sleep_start();
  });

  server.on("/service/bluetooth/start", HTTP_POST, [](){
      ESP_LOGD("[eisp32_radio]","bluetooth/start");    
      radio.recordActivity();
      radio.startBluetooth();       
      radio.sendResponse(server);
  });

  server.on("/service/bluetooth/stop", HTTP_POST, [](){
      ESP_LOGD("[eisp32_radio]","bluetooth/stop");    
      radio.recordActivity();
      radio.stopBluetooth();
      radio.sendResponse(server);
  });

  server.on("/service/restart", HTTP_POST, [](){
      ESP_LOGI("[eisp32_radio]","restart");    
      ESP.restart();
  });

  server.on("/service/streaming/start", HTTP_POST, [](){
      ESP_LOGD("[eisp32_radio]","streaming/start");    
      radio.recordActivity();
      String url = server.arg("url");        
      radio.startStreaming(url);
      radio.sendResponse(server);
  });

  server.on("/service/streaming/stop", HTTP_POST, [](){
      ESP_LOGD("[eisp32_radio]","streaming/stop");    
      radio.recordActivity();
      radio.stopStreaming();
      radio.sendResponse(server);
  });

  //server.enableCrossOrigin(true);
  // start server
  server.begin();

}

void setup(){  
  audioLogger = &Serial;
  setupWifi();
  setupServer();
  radio.startBluetooth();       


  ESP_LOGI("[eisp32_radio]","free heep: %u", ESP.getFreeHeap());    
  
  Serial.println();
  Serial.print("You can connect to ");
  Serial.println(WiFi.localIP());  
}


void loop(){
  server.handleClient();
  radio.loop();
  
  // if not used for more then n sec - we shut down
  if (radio.notActiveFor(15*60)){
      ESP_LOGI("[eisp32_radio]","shut down"); 
      esp_deep_sleep_start();
  }

}
