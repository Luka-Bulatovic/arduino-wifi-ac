// WebServer.h
#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <ESP8266WebServer.h>
#include "Displayable.h"
#include "WiFiConnection.h"

class WebServer : public Displayable {
  private:
    ESP8266WebServer server;
    WiFiConnection* connection;

  public:
    WebServer(int port, WiFiConnection* connection) : server(port), connection(connection) {}

    void begin();
    void handleClient();

    String getDisplayData() override;
};

#endif
