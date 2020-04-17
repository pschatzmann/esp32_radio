
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

void Radio::setup(){
  ssid = WiFi.SSID();
}

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
  try {
      if (a2d_sink)
        delete(a2d_sink);
      a2d_sink = NULL;
  } catch (const std::exception& e) { 
    ESP_LOGE("[eisp32_radio]","could not delete a2d_sink"); 
  }
  ESP_LOGI("[eisp32_radio]","stoped");    
}

void Radio::startStreaming(String url) {
  ESP_LOGI("[eisp32_radio]","startStreaming: %s",url.c_str());    
  streamingReady = false;
  stopBluetooth();
  stopStreaming();
  if (file==NULL)
    file = new AudioFileSourceICYStream(url.c_str());
  file->SetReconnect(5, 0);

  if (out==NULL)
    out = new AudioOutputI2S(); // (0,1) is using the internal DAC
  if (audio==NULL)
    audio = new AudioGeneratorMP3();
  audio->begin(file, out);
  streamingReady = true;
  ESP_LOGI("[eisp32_radio]","play started");    
  
}

void Radio::stopStreaming() {
  try {
    if (audio && audio->isRunning())
      audio->stop();      
  } catch (const std::exception& e) { 
    ESP_LOGE("[eisp32_radio]","could not stop audio"); 
  }

  streamingReady = false;

  try {
      if (file)
        delete(file);
      file = NULL;
  } catch (const std::exception& e) { 
    ESP_LOGE("[eisp32_radio]","could not free file"); 
  }

  try {
      if (audio)
        delete(audio);
      audio = NULL;
  } catch (const std::exception& e) { 
    ESP_LOGE("[eisp32_radio]","could not free audio"); 
  }

  try {
      if (out)
        delete(out);
      out = NULL;
  } catch (const std::exception& e) { 
    ESP_LOGE("[eisp32_radio]","could not free out"); 
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
    ESP_LOGI("[eisp32_radio]","sendResponse");    
//    AsyncResponseStream *response = request->beginResponseStream("application/json");
//    StaticJsonDocument<500> doc;
//    doc["heap"] = ESP.getFreeHeap();
//    doc["ssid"] = this->ssid;
//    doc["streaming"] = file!=NULL;
//    doc["bluetooth"] = a2d_sink!=NULL;
//    doc["bluetooth_name"] = bluetooth_name;
//    doc["stream"] = musicUrl;
//    serializeJson(doc, *response);
//    request->send(response);
    char jsonResponse[500];
    sprintf(jsonResponse, jsonFmt,ESP.getFreeHeap(),this->ssid.c_str(),file!=NULL,a2d_sink!=NULL, bluetooth_name);
    request->send(200, "application/json", jsonResponse);
    
}


void Radio::loop(){
  try {
    if (streamingReady && audio->isRunning()) {
      audio->loop();
    }
  } catch (const std::exception& e) { 
    ESP_LOGE("[eisp32_radio]","error in loop: %s", e.what()); 
  }


  // record activity every 10sec 
  if (millis() / 10000 == 0){
     if (file!=NULL && file->isOpen()){
        recordActivity();
     }
     if (a2d_sink!=NULL && a2d_sink->get_audio_state()==ESP_A2D_AUDIO_STATE_STARTED){
        recordActivity();
     }  
  }
  
}

void Radio::recordActivity(){
  lastActivity = millis() / 1000; 
}

bool Radio::notActiveFor(unsigned long delaySec){
  unsigned long current = millis() / 1000;
  return (current - lastActivity) > delaySec;
}
