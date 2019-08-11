void httpGetStatus() {
  //Serial.printf("Connecting to %s, requesting URL: %s\r\n", host.c_str(), service.c_str());
  
  WiFiClient client;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  client.println(String("GET ") + service + " HTTP/1.1");
  client.println(String("Host: ") + host);
  client.println(String("User-Agent: ") + DEVICE_NAME);
  client.println(String("Accept: */*"));
  client.println(String("Connection: close"));
  client.println(String("Pragma: no-cache"));
  client.println(String("Cache-Control: no-cache"));
  client.println();
  
  delay(500);

  while (client.available()) {
    String line = client.readStringUntil('\r');
    if( line.substring(1, 12) == "{\"status\": " ){
        if (line.substring(12, 13) == "1") {
            changeState(1);
        } else {
            changeState(0);
        }
        client.stop();
        break;
    }
  } 
  // Serial.println("Connection closed");
}
