
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

#include "ESPAsyncWebServer.h"
#include "esp32_bt_music_receiver.h"
#include "esp32_bt_music_receiver.h"
#include "AudioFileSourceICYStream.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"
#include "ArduinoJson.h"

#ifndef _RADIO.HPP_
#define _RADIO.HPP_

class Radio {

  public:
    void setup();
    void startBluetooth();
    void stopBluetooth();
    void startStreaming(String url);
    void stopStreaming();
    boolean isStart(AsyncWebServerRequest *request);
    String getMusicURL(uint8_t *data, size_t len);
    void sendResponse(AsyncWebServerRequest *request);
    void loop();
    void recordActivity();
    bool notActiveFor(unsigned long);
    
  private:
    // Music Player
    BlootoothA2DSink *a2d_sink;
    AudioGenerator *audio=NULL;
    AudioFileSourceHTTPStream *file=NULL;
    AudioOutputI2S *out=NULL;
    String bluetooth_name = "MusicPlayer";
    String musicUrl = "http://listen.181fm.com/181-blues_128k.mp3";
    const char* jsonFmt = "{ \"heap\": %d, \"ssid\": \"%s\", \"streaming\": %B, \"bluetooth\": %B, \"bluetooth_name\": \"%s\" }";
    // timer
    unsigned long lastActivity = millis()/1000;
    bool streamingReady = false;
    String ssid;


};

#endif
