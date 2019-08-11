/**
 * Konfiguracja IDE:
 * płytka:        WeMos D1 R2 & mini
 * CPU frequency: 80MHz
 * rozmiar:       4M (1M SPIFFS)
 * IwIP Variant:  v2 Lower Memory
 * Debug port:    Disabled
 * Debug level:   None
 * Erase Flash:   Only Sketch
 * Upload Speed:  921600
 */

#include <SPI.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>

#define RELAY D1 //Pin to which is attached a relay
String DEVICE_NAME = "FOTN-SWITCH-CLIENT";

#ifndef APSSID
#define APSSID "Foton switch"
#define APPSK  "secret-wifi-password"
#endif

String host = "192.168.4.1";
int httpPort = 80;
String service = "/status";
int fotonState = -1;
unsigned long previousMillis = 0;
const long interval = 10000;
bool stopped = false;

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  Serial.println("\nWake up");
  
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, HIGH);
  
  pinMode(RELAY, OUTPUT); // Set the pin to an output
  digitalWrite(BUILTIN_LED, LOW);

  wifiSetup(APSSID, APPSK);
  
  httpServerSetup();
  changeState(0);
  // ESP.deepSleep(0);
}

void loop() {
    server.handleClient();

    if (!stopped) {
      unsigned long currentMillis = millis();
      if ((currentMillis - previousMillis >= interval) || (currentMillis - previousMillis <= 0)) {
        previousMillis = currentMillis;
        httpGetStatus();
      }
    }
}

