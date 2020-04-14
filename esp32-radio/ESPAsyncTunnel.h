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
