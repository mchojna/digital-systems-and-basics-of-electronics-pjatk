#include <Wire.h>

 

const int red_pin = 11;

const int yellow_pin = 10;

const int blue_pin = 9;

const int white_pin = 6;

const int led_pins[] = {red_pin, yellow_pin, blue_pin, white_pin};

volatile bool state = false;

 

void receiveData(int byteCount) {

 while (Wire.available()) {

   state = Wire.read();

 }

}

 

void setup() {

 for (int i = 0; i < 4; i++) {

   pinMode(led_pins[i], OUTPUT);

   digitalWrite(led_pins[i], LOW);

 }

 

 Wire.begin(8);

 Wire.onReceive(receiveData);
}
 

void loop() {

 if (state) {

   for (int i = 0; i < 4; i++) {

     digitalWrite(led_pins[i], HIGH);

   }

 } else {

   for (int i = 0; i < 4; i++) {

     digitalWrite(led_pins[i], LOW);

   }

 }

}
