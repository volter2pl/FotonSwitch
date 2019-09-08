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
#include <WebSocketsServer.h>
#include <Hash.h>
#include "config.h"

#define FOTON D0
int fotonState = -1;
WebSocketsServer webSocket = WebSocketsServer(port);

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {

    switch(type) {
        case WStype_DISCONNECTED:
             Serial.printf("[%u] Disconnected!\n", num);
             break;
        case WStype_CONNECTED:
             {
               IPAddress ip = webSocket.remoteIP(num);
               Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
               // send message to client
               if (fotonState) {
                   webSocket.sendTXT(num, "1");
               } else {
                  webSocket.sendTXT(num, "0");
               }
             }
             break;
        case WStype_TEXT:
             Serial.printf("[%u] received TEXT: %s\n", num, payload);
             break;
        case WStype_BIN:
             Serial.printf("[%u] received BINARY length: %u\n", num, length);
             hexdump(payload, length);
             // send message to client
             // webSocket.sendBIN(num, payload, length);
             break;
    }
}

void setup() {
    Serial.begin(115200);

    pinMode(FOTON, INPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    ledOn();

    WiFi.softAP(wifi_ssid, wifi_pass);
    IPAddress myIP = WiFi.softAPIP();
    Serial.println();
    Serial.print("AP IP address: ");
    Serial.println(myIP);

    webSocket.begin();
    webSocket.onEvent(webSocketEvent);
    ledOff();
}

void loop() {
    changeState(digitalRead(FOTON));
    webSocket.loop();
}

