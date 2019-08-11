void wifiSetup(String ssid, String password) {
  WiFi.mode(WIFI_STA);
  Serial.print("    ssid: "); Serial.println(ssid);
  Serial.print("password: "); Serial.println(password);
  WiFi.begin(ssid.c_str(), password.c_str());
  Serial.println("");

  //Wait for WIFI connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("MAC address: ");
  Serial.println(WiFi.macAddress());  
}
