
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

#include "Radio.hpp"

void Radio::startBluetooth() {
  ESP_LOGI("[eisp32_radio]","bluetooth");    
  stopStreaming();
  if (a2d_sink==NULL){
      a2d_sink = new BlootoothA2DSink();
      a2d_sink->start((char*)bluetooth_name.c_str());
      ESP_LOGI("[eisp32_radio]","bluetooth started");    
  }
}

void Radio::stopBluetooth() {
  if (a2d_sink!=NULL){
      delete(a2d_sink);
      a2d_sink = NULL;
  }
  ESP_LOGI("[eisp32_radio]","stoped");    
}

void Radio::startStreaming(String url) {
  ESP_LOGI("[eisp32_radio]","startStreaming: %s",url.c_str());    
  stopBluetooth();
  stopStreaming();
  file = new AudioFileSourceICYStream(url.c_str());
  file->SetReconnect(5, 0);
  
  out = new AudioOutputI2S(); // (0,1) is using the internal DAC
  audio = new AudioGeneratorMP3();
  audio->begin(file, out);
  ESP_LOGI("[eisp32_radio]","play started");    
  
}

void Radio::stopStreaming() {
  if (audio!=NULL){
      audio->stop();
      delete(audio);
      audio = NULL;
  }
  if (file!=NULL) {
      delete(file);
      file = NULL;
  }
  if (out!=NULL){
      delete(out);
      out = NULL;
  }
  ESP_LOGI("[eisp32_radio]","stoped"); 
}

boolean Radio::isStart(AsyncWebServerRequest *request) {
    bool start = true;
    if(request->hasParam("action")) {
      AsyncWebParameter* p = request->getParam("action");
      String action = p->value();
      if (action.equals("stop")){
          start = false;
      }
    }
    ESP_LOGI("[eisp32_radio]","isStart -> %s",start?"true":false);    
    return start;
}

String Radio::getMusicURL(uint8_t *data, size_t len) {
    DynamicJsonDocument doc(len);
    DeserializationError err = deserializeJson(doc, data);
    if (err) {
      Serial.print(F("deserializeJson() failed with code "));
      Serial.println(err.c_str());
      ESP_LOGE("[eisp32_radio]","deserializeJson() failed with code %s", err.c_str());    
      return musicUrl;
    } else {
      String url = doc["url"]; 
      musicUrl = url;    
      ESP_LOGI("[eisp32_radio]","getMusicURL %s", musicUrl.c_str());          
    }

    return musicUrl;
}

void Radio::sendResponse(AsyncWebServerRequest *request) {
    ESP_LOGI("[eisp32_radio]","info");    
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    StaticJsonDocument<200> doc;
    doc["heap"] = ESP.getFreeHeap();
    doc["ssid"] = WiFi.SSID();
    doc["streaming"] = audio!=NULL;
    doc["bluetooth"] = a2d_sink!=NULL;
    doc["bluetooth_name"] = bluetooth_name;
    doc["stream"] = musicUrl;
    serializeJson(doc, *response);
    request->send(response);
}

void Radio::loop(){
  if (audio && audio->isRunning()) {
    audio->loop();
  }
}
