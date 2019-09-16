/**
 * IDE:           Arduino 1.8.4
 * board:         WeMos D1 R2 & mini
 * CPU frequency: 80MHz
 * rozmiar:       4M (1M SPIFFS)
 * IwIP Variant:  v2 Lower Memory
 * Debug port:    Disabled
 * Debug level:   None
 * Erase Flash:   Only Sketch
 * Upload Speed:  921600
 * Lib:           https://github.com/Links2004/arduinoWebSockets
 */

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WebSocketsClient.h>
#include <Hash.h>
#include "config.h"

ESP8266WiFiMulti WiFiMulti;
WebSocketsClient webSocket;

#define RELAY D1
int fotonState = -1;

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
    switch(type) {
        case WStype_DISCONNECTED:
             // Serial.printf("[WSc] Disconnected!\n");
             break;
        case WStype_CONNECTED:
             Serial.printf("[WSc] Connected to url: %s\n",  payload);
            // send message to server when Connected
            webSocket.sendTXT("Connected");
            break;
        case WStype_TEXT:
             // Serial.printf("[WSc] received TEXT: %s\n", payload);
             if (strncmp((const char*)payload, "1", 1) == 0) {
                 changeState(1);
             }
             if (strncmp((const char*)payload, "0", 1) == 0) {
                changeState(0);
             }
             break;
        case WStype_BIN:
             Serial.printf("[WSc] received BINARY length: %u\n", length);
             hexdump(payload, length);
             // send data to server
             // webSocket.sendBIN(payload, length);
             break;
    }
}

void setup() {
  Serial.begin(115200);

  pinMode(BUILTIN_LED, OUTPUT);
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, LOW);
  ledOn();

  WiFiMulti.addAP(wifi_ssid, wifi_pass);
  connecting();

  webSocket.begin(host, port, "/");
  webSocket.onEvent(webSocketEvent);

  ledOff();
}

void connecting() {
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    ledOn();
    connecting();
    ledOff();
  }
  
  webSocket.loop();
}

