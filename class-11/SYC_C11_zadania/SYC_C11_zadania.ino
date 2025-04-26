#include<Servo.h>

const int trigPin = 9;
const int echoPin  = 6;
const int potPin = A0;
const int servoPin = 5;

long duration;
int  distance;

const int buttonOne = A1;
const int buttonTwo = A2; 

bool firstButton = false;
bool secondButton = false;

Servo servo;

int radarAngel = 0;
bool turnRight = true;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  servo.attach(servoPin);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  pinMode(buttonOne, INPUT);
  pinMode(buttonTwo, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  firstButton = analogRead(buttonOne);
  secondButton = analogRead(buttonTwo);

  if(firstButton && secondButton){
    int potValue = analogRead(potPin);  
    float mappedValue = pow(potValue / 1023.0, 3); 
    int angle = map(mappedValue * 1023, 0, 1023, 0, 180);
    servo.write(angle);
    
    delay(15);
  }else if (firstButton){
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH);
    long distance = (duration / 2) / 29.1;

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    delay(120);  
  }else if(secondButton){

    if(turnRight && radarAngel < 180){
      radarAngel += 1;
    } else {
      turnRight = false;
    }

    if(!turnRight && radarAngel > 0 ){
      radarAngel -= 1;
    } else {
      turnRight = true;
    }

    servo.write(radarAngel);
  
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH);
    long distance = (duration / 2) / 29.1;

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    delay(120);  
  }
}
