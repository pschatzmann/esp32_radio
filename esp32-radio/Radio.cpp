
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

unsigned long Radio::lastActivity = millis()/1000;

Radio::Radio() {
}

void Radio::setup(){
  ssid = WiFi.SSID();
}

void Radio::startBluetooth() {
  ESP_LOGI("[eisp32_radio]","bluetooth");    
  stopStreaming();
  if (a2d_sink==NULL){
      a2d_sink = new BluetoothA2DSink();
      a2d_sink->set_on_data_received(recordActivity);
      a2d_sink->start((char*)bluetooth_name.c_str());
      ESP_LOGI("[eisp32_radio]","bluetooth started");    
  };
}

void Radio::stopBluetooth() {
  try {
      if (a2d_sink!=NULL)
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
  if (!url.isEmpty()){
    if (file==NULL)
      file = new AudioFileSourceICYStream(url.c_str());
    file->SetReconnect(5, 0);
  
    if (out==NULL)
      out = new AudioOutputI2S(); // (0,1) is using the internal DAC
    if (audio==NULL)
      audio = new AudioGeneratorMP3();
    audio->begin(file, out);
  }
  streamingReady = true;
  ESP_LOGI("[eisp32_radio]","play started");    
  
}

void Radio::stopStreaming() {
  try {
    if (audio!=NULL && audio->isRunning())
      audio->stop();      
  } catch (const std::exception& e) { 
    ESP_LOGE("[eisp32_radio]","could not stop audio"); 
  }

  try {
      if (audio!=NULL)
        delete(audio);
      audio = NULL;
  } catch (const std::exception& e) { 
    ESP_LOGE("[eisp32_radio]","could not free audio"); 
  }

  try {
      if (file!=NULL)
        delete(file);
      file = NULL;
  } catch (const std::exception& e) { 
    ESP_LOGE("[eisp32_radio]","could not free file"); 
  }

  try {
      if (out!=NULL)
        delete(out);
      out = NULL;
  } catch (const std::exception& e) { 
    ESP_LOGE("[eisp32_radio]","could not free out"); 
  }
  
  streamingReady = false;
  ESP_LOGI("[eisp32_radio]","stoped"); 
}

void Radio::sendResponse(WebServer &server) {
    ESP_LOGI("[eisp32_radio]","sendResponse");    
    //AsyncResponseStream *response = request->beginResponseStream("application/json");
    sprintf(jsonResponse, jsonFmt, ESP.getFreeHeap(), this->ssid.c_str(), streamingReady?"true":"false", a2d_sink!=NULL?"true":"false", bluetooth_name.c_str());
    server.send(200, "application/json", jsonResponse);

}


void Radio::loop(){
  try {
    if (audio!=NULL && audio->isRunning()) {
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
