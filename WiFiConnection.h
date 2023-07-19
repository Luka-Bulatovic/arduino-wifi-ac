// WiFiConnection.h
#ifndef WIFICONNECTION_H
#define WIFICONNECTION_H

#include <ESP8266WiFi.h>
#include "Displayable.h"

class WiFiConnection : public Displayable {
  private:
    const char* ssid;
    const char* password;
    bool isConnecting;

  public:
    WiFiConnection(const char* ssid, const char* password)
      : ssid(ssid), password(password)
    {
      this->isConnecting = false;
    }

    void connect();
    bool isConnected();

    String getDisplayData() override;
};

#endif