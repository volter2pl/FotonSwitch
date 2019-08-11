void httpServerSetup() {
  server.on("/", HandleRoot);
  server.on("/switch", HandleSwitch);
  server.on("/reset", HandleReset);
  server.onNotFound( HandleNotFound );
  server.begin();
  Serial.println("HTTP server started at ip " + WiFi.localIP().toString() );  
}

void HandleRoot(){
  String html = "";
  html += "<h1>Switch status: ";
  html += fotonState;
  if (stopped) {
    html += " (stopped)";
  }
  html += "</h1><br>\n";
  html += "<a href=/switch>switch</a><br>\n";
  html += "<a href=/reset>reset</a><br>\n";
  server.send(200, "text/html", html);
}

void HandleSwitch(){
  if (fotonState == 0) {
    changeState(1);
  } else {
    changeState(0);
  }
  stopped = true;
  String response = "{\"switch-status\" : " + String(fotonState) + ", \"loop-status\" : \"stop\"}";
  server.send( 200, "application/json", response);
}

void HandleReset(){
  stopped = false;
  String response = "{\"switch-status\" : " + String(fotonState) + ", \"loop-status\" : \"running\"}";
  server.send( 200, "application/json", response);
}

void HandleNotFound(){
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/html", message);
}
