// WebServer.h
#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <ESP8266WebServer.h>
#include "Displayable.h"
#include "WiFiConnection.h"
#include "SerialCommunication.h"

class WebServer : public Displayable {
  private:
    ESP8266WebServer server;
    WiFiConnection* connection;
    SerialCommunication* communication;

    String additionalDisplayData;

  public:
    WebServer(int port, WiFiConnection* connection, SerialCommunication* communication) : server(port), connection(connection), communication(communication), additionalDisplayData("") {}

    void begin();
    void handleClient();

    String getDisplayData() override;
};

#endif
