// WebServer.cpp
#include "WebServer.h"

void WebServer::begin() {
  server.on("/", [this]() {
    server.send(200, "text/plain", "Hello from ESP8266");
  });

  // Define the /ac route
  server.on("/ac", [this]() {
    // Retrieve the 'params' query parameter
    String params = server.arg("params");

    communication->sendMessage("ac", params.c_str());

    additionalDisplayData = "AC:\n";
    additionalDisplayData += "Temp: ";
    additionalDisplayData += params.substring(0, 1);
    additionalDisplayData += "; Mode: " + params.substring(2, 2);
    additionalDisplayData += "; Fan: " + params.substring(3, 3);

    server.send(200, "text/plain", "OK");
  });

  this->server.begin();
}

void WebServer::handleClient() {
  if (this->connection->isConnected()) {
    this->server.handleClient();
  }
}

String WebServer::getDisplayData() {
  String displayData = "Server: ";
  displayData += (this->connection->isConnected()) ? "running" : "not running";
  
  if(additionalDisplayData != "")
    displayData += additionalDisplayData;

  return displayData;
}