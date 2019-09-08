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
      digitalWrite(RELAY, HIGH);
    } else {
      ledOff();
      digitalWrite(RELAY, LOW);
    }
  }
}

