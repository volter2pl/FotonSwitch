void ledOn() {
  digitalWrite(BUILTIN_LED, LOW);
}

void ledOff() {
  digitalWrite(BUILTIN_LED, HIGH);
}

void changeState(int state) {
  if (fotonState != state) {
    fotonState = state;
    if (state) {
      ledOn();
      webSocket.broadcastTXT("1");
    } else {
      ledOff();
      webSocket.broadcastTXT("0");
    }
  }
}

