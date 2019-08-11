String IpAddress2String(const IPAddress& ipAddress)
{
  return String(ipAddress[0]) + String(".") +\
  String(ipAddress[1]) + String(".") +\
  String(ipAddress[2]) + String(".") +\
  String(ipAddress[3])  ; 
}

void changeState(int state) {
  if (fotonState != state) {
    fotonState = state;
    if (state) {
      Serial.println("1");
      digitalWrite(LED_BUILTIN, LOW);
    } else {
      Serial.println("0");
      digitalWrite(LED_BUILTIN, HIGH);
    }
  }
}

