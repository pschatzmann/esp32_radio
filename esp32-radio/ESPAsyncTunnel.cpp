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

#include "ESPAsyncTunnel.h"
#include "mdns.h"

/**
 * ClientRequestTunnel 
 */
ClientRequestTunnel::ClientRequestTunnel() {
   ESP_LOGD("[ClientRequestTunnel]","Constructor!");    
}

bool ClientRequestTunnel::open(String target, String url) {
   return open(getForwardURL(target, url));
}

bool ClientRequestTunnel::open(String url) {
  ESP_LOGD("[ClientRequestTunnel]","open");    
  this->url = url;
  this->http = new HTTPClient();
  if (!http->begin(url)){
    ESP_LOGE("[ClientRequestTunnel]","Unable to connect!");    
    ok = false;
    return ok;   
  }
  ESP_LOGI("[ClientRequestTunnel]","Connected!");    
  this->http->collectHeaders(headerkeays, 1);
  this->httpCode = http->GET();
  if(this->httpCode == HTTP_CODE_OK || this->httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
      ok = true;
      ESP_LOGI("[ClientRequestTunnel]","HttpCode -> OK");           
  } else {
      ok = false;
      ESP_LOGE("[ClientRequestTunnel]","GET... failed, error: %s\n", http->errorToString(httpCode).c_str());
  }
  return ok;
}

ClientRequestTunnel::~ClientRequestTunnel() {
  ESP_LOGD("[ClientRequestTunnel]","Destructor!");   
  if (http){ 
    http->end();
    delete(http);
  }
}

bool ClientRequestTunnel::isOK() {
  return this->ok;
}

int ClientRequestTunnel::getHttpCode() {
  return this->httpCode;
}

String ClientRequestTunnel::getString() {
  return http ? http->getString() : "";
}

Stream* ClientRequestTunnel::getStream() {
  return (http && http->connected()) ? http->getStreamPtr() : NULL;
}

String ClientRequestTunnel::getContentType() {
  return http ? http->header(headerkeays[0]) : "";
}

size_t ClientRequestTunnel::getSize() {
  return http ? http->getSize() : 0 ;
}

HTTPClient* ClientRequestTunnel::getHTTPClient() {
  return http;
}

String ClientRequestTunnel::getForwardURL(String target_address, String url) {
  String forward_path;
  if (target_address.isEmpty()){
      forward_path = url;
  } else if (url.indexOf("http",0)==0) {
    // does it start with http ?      
    int pos = url.indexOf("/",9);
    String requestd_path = url.substring(pos);
    forward_path =  target_address + requestd_path;
  } else {
    forward_path =  target_address + url;
  }
  
  ESP_LOGI("[ClientRequestTunnel]","%s -> %s\n", url.c_str(),forward_path.c_str());
  return forward_path;
}
