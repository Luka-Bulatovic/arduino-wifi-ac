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

  // Start web server
  serverPtr = new WebServer(80, connectionPtr);
  serverPtr->begin();

  // Setup Serial Communication between ATMega and ESP8266
  communication = new SerialCommunication(&Serial);

  // Income message handlers
  //communication->registerHandler("test", handleTestMessage);
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

  communication->sendMessage("display", sendBuffer);

  delay(1000);
}
