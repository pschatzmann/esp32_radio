#include <Arduino.h>
#include "HTTPClient.h"
#include "ESPAsyncWebServer.h"

#ifndef _ESPAsyncTunnel_H_
#define _ESPAsyncTunnel_H_


/**
 * Http Client which returns the data from a remove Server
 */
class ClientRequestTunnel {
  public:
    ClientRequestTunnel();
    bool open(String targetUrl, String url);
    bool open(String url);
    ~ClientRequestTunnel();
    String getString();
    Stream* getStream();
    String getContentType();
    size_t getSize();
    HTTPClient* getHTTPClient();
    bool isOK();
    int getHttpCode();
    String getForwardURL(String target, String url);
    
  private:      
      bool ok = false;
      HTTPClient *http;
      String url;
      const char* headerkeays[1] = {"Content-Type"};
      int httpCode;
};


#endif
