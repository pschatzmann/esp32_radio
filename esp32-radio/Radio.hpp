
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

//#include "ESPAsyncWebServer.h"
#include <WebServer.h>

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
    Radio();
    void setup();
    void startBluetooth();
    void stopBluetooth();
    void startStreaming(String url);
    void stopStreaming();
    void sendResponse(WebServer &server);
    void loop();
    static void recordActivity();
    static bool notActiveFor(unsigned long);
    
  private:
    // Music Player
    BlootoothA2DSink *a2d_sink=NULL;
    AudioGenerator *audio=NULL;
    AudioFileSourceHTTPStream *file=NULL;
    AudioOutputI2S *out=NULL;
    String ssid;
    String bluetooth_name = "MusicPlayer";
    String musicUrl = "http://listen.181fm.com/181-blues_128k.mp3";
    //StaticJsonDocument<500> doc;
    const char* jsonFmt = "{ \"heap\": %d, \"ssid\": \"%s\", \"streaming\": %B, \"bluetooth\": %B, \"bluetooth_name\": \"%s\" }";
    char jsonResponse[500];
    // timer
    bool streamingReady = false;
    static unsigned long lastActivity;


};

#endif
