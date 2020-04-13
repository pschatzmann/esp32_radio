
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
    void startBluetooth();
    void stopBluetooth();
    void startStreaming(String url);
    void stopStreaming();
    boolean isStart(AsyncWebServerRequest *request);
    String getMusicURL(uint8_t *data, size_t len);
    void sendResponse(AsyncWebServerRequest *request);
    void loop();
    AudioGenerator *audio;
    
  private:
    // Music Player
    BlootoothA2DSink *a2d_sink;
    AudioFileSourceHTTPStream *file;
    AudioOutputI2S *out;
    String bluetooth_name = "MusicPlayer";
    String musicUrl = "http://listen.181fm.com/181-blues_128k.mp3";

};

#endif
