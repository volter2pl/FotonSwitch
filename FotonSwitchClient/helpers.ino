void changeState(int state) {
  if (fotonState != state) {
    fotonState = state;
    if (state) {
      Serial.println("new state 1");
      digitalWrite(LED_BUILTIN, LOW);
      digitalWrite(RELAY, HIGH);
    } else {
      Serial.println("new state 0");
      digitalWrite(LED_BUILTIN, HIGH);
      digitalWrite(RELAY, LOW);
    }
  }
}

