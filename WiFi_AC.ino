// WiFi.ino
#include <ESP8266WiFi.h>
#include "WiFiConnection.h"
#include "WebServer.h"
#include "SerialCommunication.h"

using namespace std;

// WiFi Connection info
const char* wifiSSID = "Bulatovic";
const char* wifiPassword = "tedi1234";

WiFiConnection* connectionPtr;
WebServer* serverPtr;
SerialCommunication* communication;

unsigned long lastDisplayUpdate = 0;
String lastDisplayStr = "";

char* sendBuffer;

void handleTestMessage(const char* message) {

}

void setup() {
  Serial.begin(9600);

  while(!Serial) {;}
  
  sendBuffer = new char[100];
  
  // Connect to WiFi
  connectionPtr = new WiFiConnection(wifiSSID, wifiPassword);
  connectionPtr->connect();

  // Setup Serial Communication between ATMega and ESP8266
  communication = new SerialCommunication();
  communication->setStream(&Serial);

  // Start web server
  serverPtr = new WebServer(80, connectionPtr, communication);
  serverPtr->begin();
}

void loop() {
  String displayStr = connectionPtr->getDisplayData() + "\n" + serverPtr->getDisplayData() + '\0';
  strcpy(sendBuffer, displayStr.c_str());

  communication->handleMessage();

  if(connectionPtr->isConnected()) {
    serverPtr->handleClient();
  }
  else {
    connectionPtr->connect();
  }

  // Send update to display
  // Get the current time
  unsigned long currentTime = millis();

  // Check if one second (1000 ms) has passed since the last time the function was called
  if (currentTime - lastDisplayUpdate >= 1000) {
    // Call your function here
    if(displayStr != lastDisplayStr)
    {
      lastDisplayStr = displayStr;
      communication->sendMessage("display", sendBuffer);
    }

    // Update the last time the function was called
    lastDisplayUpdate = currentTime;
  }

  delay(1000);
}
