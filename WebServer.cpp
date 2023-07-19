// WebServer.cpp
#include "WebServer.h"

void WebServer::begin() {
  server.on("/", [this]() {
    server.send(200, "text/plain", "Hello from ESP8266");
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
  return displayData;
}