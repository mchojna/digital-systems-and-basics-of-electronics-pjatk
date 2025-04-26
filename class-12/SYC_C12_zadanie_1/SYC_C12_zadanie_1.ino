const int red_pin = 11;
const int yellow_pin = 10;
const int blue_pin = 9;
const int white_pin = 6;
const int button_pin = 2;
 
const int led_pins[] = {red_pin, yellow_pin, blue_pin, white_pin};
const float frequencies[] = {0.6, 1.0, 1.3, 2.5};
 
volatile bool state = false;
volatile unsigned long last_debounce_time = 0;
 
void interrupt_button() {
   unsigned long current_time = millis();
   if (current_time - last_debounce_time > 200) {
       state = !state;
       last_debounce_time = current_time;
   }
}
 
void setup() {
   for (int i = 0; i < 4; i++) {
       pinMode(led_pins[i], OUTPUT);
       digitalWrite(led_pins[i], LOW);
   }
   pinMode(button_pin, INPUT_PULLUP);
   attachInterrupt(digitalPinToInterrupt(button_pin), interrupt_button, FALLING);
}
 
void loop() {
   if (!state) {
       for (int i = 0; i < 4; i++) {
           unsigned long period = (unsigned long)(1000.0 / frequencies[i]);
           if ((millis() % period) < (period / 2)) {
               digitalWrite(led_pins[i], HIGH);
           } else {
               digitalWrite(led_pins[i], LOW);
           }
       }
   } else {
       unsigned long current_time = millis();
       const unsigned long step_time = 1000;
       int current_group = (current_time / step_time) % 4;
       for (int i = 0; i < 4; i++) {
           if (i == current_group) {
               digitalWrite(led_pins[i], HIGH);
           } else {
               digitalWrite(led_pins[i], LOW);
           }
       }
   }
}
