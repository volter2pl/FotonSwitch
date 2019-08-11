void handleRoot() {
  String html = "";
  html += "<h1>Foton <a href=/status>status</a>: ";
  html += fotonState;
  html += "</h1><br>\n";
  html += client_status();
  server.send(200, "text/html", html);
}

String client_status() {
  String m = "";
  unsigned char number_client;
  struct station_info *stat_info;
  struct ip4_addr *IPaddress;
  String address;
  String clientIP = server.client().remoteIP().toString();

  number_client= wifi_softap_get_station_num();
  stat_info = wifi_softap_get_station_info();

  m += "Total Connected Clients: "; m += number_client; m += "<br>\n";
  m += "<ul>\n";
    while (stat_info != NULL) {
      IPaddress = &stat_info->ip;
      address = IpAddress2String(IPaddress->addr);
      m += "<li>";
      if (address != clientIP) {
          m += "<a href=http://" + address + ">" + address + "</a>";
      } else {
          m += address;
      }

      m += " (";
      m += String(stat_info->bssid[0], HEX) + ":";
      m += String(stat_info->bssid[1], HEX) + ":";
      m += String(stat_info->bssid[2], HEX) + ":";
      m += String(stat_info->bssid[3], HEX) + ":";
      m += String(stat_info->bssid[4], HEX) + ":";
      m += String(stat_info->bssid[5], HEX) + ")</li>\n";
      stat_info = STAILQ_NEXT(stat_info, next);
    }
  m += "</ul><br>\n";
  return m;
}

void handleStatus() {
  if (fotonState) {
      server.send(200, "application/json", "{\"status\": 1}");
  } else {
      server.send(200, "application/json", "{\"status\": 0}");
  }
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

