// SerialCommunication.h
#ifndef SERIALCOMMUNICATION_H
#define SERIALCOMMUNICATION_H

#include <Arduino.h>
#include <Stream.h>
#include "Map.h"  // #include <ArxContainer.h>

class SerialCommunication {
private:
  typedef void (*MessageHandler)(const char* message);
  const static byte bufferSize = 100;
  char incomingDataBuffer[bufferSize];

  Stream* stream;
  Map<char*, MessageHandler> handlers;
  bool newDataAvailable = false;

  static const char startMessageMarker = '<';
  static const char endMessageMarker = '>';

public:
  static const char separator = '#';

  void sendMessage(const char* tag, const char* message);
  void handleMessage();
  void registerHandler(char* messageType, MessageHandler handler);
  void receiveIncomingData();
  void setStream(Stream* stream);

private:
  void handleMessage(char* message);
};

#endif
