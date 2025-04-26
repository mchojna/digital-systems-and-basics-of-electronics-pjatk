// Master Arduino (5V)

const int red_pin = 11;

const int yellow_pin = 10;

const int blue_pin = 9;

const int white_pin = 6;

const int led_pins[] = {red_pin, yellow_pin, blue_pin, white_pin};

const float frequencies[] = {0.6, 1.0, 1.3, 2.5};

 

void setup() {

 for (int i = 0; i < 4; i++) {

   pinMode(led_pins[i], OUTPUT);

   digitalWrite(led_pins[i], LOW);

 }

 Serial.begin(9600);

}

 

void loop() {

 static bool state = false;

 

 if (Serial.available() > 0) {

   char cmd = Serial.read();

   if (cmd == 't') {

     state = !state;

     Serial.write(state ? '1' : '0');

   }

 }

 

 updateLEDs(state);

}

 

void updateLEDs(bool state) {

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

     digitalWrite(led_pins[i], i == current_group ? HIGH : LOW);

   }

 }

}

 

Kod Slave:

// Slave Arduino (3.3V)

const int red_pin = 11;

const int yellow_pin = 10;

const int blue_pin = 9;

const int white_pin = 6;

const int led_pins[] = {red_pin, yellow_pin, blue_pin, white_pin};

const float frequencies[] = {0.6, 1.0, 1.3, 2.5};

 

void setup() {

 for (int i = 0; i < 4; i++) {

   pinMode(led_pins[i], OUTPUT);

   digitalWrite(led_pins[i], LOW);

 }

 Serial.begin(9600);

}

 

void loop() {

 static bool state = false;

 

 if (Serial.available() > 0) {

   char cmd = Serial.read();

   if (cmd == '1') state = true;

   else if (cmd == '0') state = false;

 }

 

 updateLEDs(state);

}

 

void updateLEDs(bool state) {

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

     digitalWrite(led_pins[i], i == current_group ? HIGH : LOW);

   }

 }

}