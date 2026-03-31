int potPin = A0;
int ledPin = 2;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int val = analogRead(potPin);
  Serial.println(val); // Hantar nilai ke Python

  // Baca arahan dari Python (kalau ada)
  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == '1') {
      digitalWrite(ledPin, HIGH);
    } else if (command == '0') {
      digitalWrite(ledPin, LOW);
    }
  }
  delay(100);
}