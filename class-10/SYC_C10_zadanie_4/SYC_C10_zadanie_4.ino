bool ledState = false;
bool previousButtonState = HIGH;

unsigned long previousDebounceTime = 0;
unsigned long debounceDelay = 100;

void setup() {
  // put your setup code here, to run once:
  pinMode(4,  INPUT_PULLUP);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  bool currentButtonState = digitalRead(4);

  if (currentButtonState != previousButtonState) {
    previousDebounceTime = millis();
  }

  if ((millis() - previousDebounceTime) > debounceDelay) {
    if (currentButtonState == LOW && previousButtonState == HIGH) {
      ledState = !ledState;
      if(ledState) {
        digitalWrite(13, HIGH);
      } else {
        digitalWrite(13, LOW);
      }
    }
  }
  
  previousButtonState = currentButtonState;
}
