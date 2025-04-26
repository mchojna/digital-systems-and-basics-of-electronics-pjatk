bool ledState = false;
bool buttonPressed = false;
bool previousButtonState = HIGH;

void setup() {
  // put your setup code here, to run once:
  pinMode(4,  INPUT_PULLUP);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  bool currentButtonState = digitalRead(4);

  if(currentButtonState == LOW && previousButtonState == HIGH && !buttonPressed) {
    buttonPressed = true;
    ledState = !ledState;
    if(ledState) {
      digitalWrite(13, HIGH);
    } else {
      digitalWrite(13, LOW);
    }
  }

  if(currentButtonState == HIGH && buttonPressed) {
    buttonPressed = false;
  }

  previousButtonState = currentButtonState;
}
