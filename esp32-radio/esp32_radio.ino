#include <vector>
#include "AsyncTCP.h"
#include "ESPAsyncWebServer.h"
#include "ESPAsyncTunnel.h"
#include "ArduinoJson.h"
#include "esp32_bt_music_receiver.h"


// WIFI
const String ssid = "your ssid";
const String password = "password";

// Web Server & Sevices
AsyncWebServer server(80);
char* indexPath = "/esp32_radio/vue-radio/dist/index.html";

// Music Player
BlootoothA2DSink *a2d_sink;
AudioGenerator *audio;
AudioFileSourceHTTPStream *file;
AudioOutputI2S *out;
String bluetooth_name = "MusicPlayer"


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
      ESP_LOGI("[eisp32_radio]","info");    
      AsyncResponseStream *response = request->beginResponseStream("application/json");
      StaticJsonDocument<200> doc;
      doc["heap"] = ESP.getFreeHeap();
      doc["ssid"] = WiFi.SSID();
      doc["streaming"] = audio!=NULL;
      doc["bluetooth"] = a2d_sink!=NULL;
      doc["bluetooth-name"] ) bluetooth_name;
      serializeJson(doc, *response);
      request->send(response);
  });

  //Shut down server
  server.on("/service/shutdown", HTTP_POST, [](AsyncWebServerRequest *request){
      ESP_LOGI("[eisp32_radio]","shutdown");    
      esp_deep_sleep_start();
  });

  server.on("/service/bluetooth", HTTP_POST, [](AsyncWebServerRequest *request){
      ESP_LOGI("[eisp32_radio]","bluetooth");    
      if (a2d_sink==null){
          a2d_sink = new BlootoothA2DSink();
          a2d_sink->start(bluetooth_name);
          ESP_LOGI("[eisp32_radio]","bluetooth started");    
      }
  });

  server.on("/service/play", HTTP_POST, [](AsyncWebServerRequest *request){
      ESP_LOGI("[eisp32_radio]","play");    
      if(request->hasParam("url")) {
        AsyncWebParameter* p = request->getParam("url");
        String url = p->value();
        ESP_LOGI("[eisp32_radio]","play url is %s",url);    

        if (file!=null) {
            delete(file);
        }
        file = new AudioFileSourceICYStream(url);
        file->SetReconnect(5, 0);
        
        if (out == null){
          out = new AudioOutputI2S(); // (0,1) is using the internal DAC
        }
        if (audio==null){
          audio = new AudioGeneratorMP3();
        }
        audio->begin(file, out);
        ESP_LOGI("[eisp32_radio]","play started");    
      }

  });

  server.on("/service/stop", HTTP_POST, [](AsyncWebServerRequest *request){
    ESP_LOGI("[eisp32_radio]","stop");    
    if (a2d_sink!=null){
        a2d_sink->stop();
        delete(a2d_sink);
    }
    if (audio!=null){
        audio->stop();
        delete(audio);
    }
    if (file!=null) {
        delete(file);
    }
    if (out!=null){
        delete(out);
    }
    ESP_LOGI("[eisp32_radio]","stoped");    
  });

  // start server
  server.begin();
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
  if (audio && audio->isRunning()) {
    audio->loop();
  }
}
