#include <Servo.h>

Servo myServo;
const int potPin = A0;   // Tengah Potentiometer
const int ledPin = 13;   // Kaki Panjang LED (Kaki Pendek ke GND)
const int servoPin = 9;  // Wayar Oren Servo

void setup() {
  Serial.begin(9600);    // Mesti 9600
  myServo.attach(servoPin);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int potValue = analogRead(potPin);
  int angle = map(potValue, 0, 1023, 0, 180);
  
  myServo.write(angle); // Servo gerak ikut Pot
  
  // LED nyala kalau pusing pot lebih 50%
  if (potValue > 512) digitalWrite(ledPin, HIGH);
  else digitalWrite(ledPin, LOW);
  
  // HANTAR DATA KE PYTHON
  Serial.println(potValue); 
  
  delay(50); 
}