// WiFiConnection.cpp
#include "WiFiConnection.h"

void WiFiConnection::connect() {
  this->isConnecting = true;
  WiFi.begin(this->ssid, this->password);

  int attempts = 0;
  int maxAttempts = 30;  // Maximum number of attempts before considering it a timeout

  while (WiFi.status() != WL_CONNECTED && attempts < maxAttempts) {
    delay(1000);
    attempts++;
  }

  this->isConnecting = false;
}

bool WiFiConnection::isConnected() {
  return WiFi.status() == WL_CONNECTED;
}

String WiFiConnection::getDisplayData() {
  String displayData = "WiFi: ";
        
  if (this->isConnecting) {
    displayData += "Connecting...";
  }
  else {
    if (WiFi.status() == WL_CONNECTED) {
      displayData = "IP: " + WiFi.localIP().toString();
    } else {
      displayData = "Not Connected";
    }
  }

  return displayData;
}