#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#ifndef APSSID
#define APSSID "Foton switch"
#define APPSK  "secret-wifi-password"
#endif

const char *ssid = APSSID;
const char *password = APPSK;

const int fotonPin = D0;
int fotonState = -1;

ESP8266WebServer server(80);

void setup() {
  delay(1000);

  pinMode(fotonPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
    
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.on("/status", handleStatus);
  server.onNotFound(HandleNotFound);
  server.begin();
  Serial.println("HTTP server started");
  
  changeState(digitalRead(fotonPin));
}

void loop() {
  changeState(digitalRead(fotonPin));
  server.handleClient();
}

