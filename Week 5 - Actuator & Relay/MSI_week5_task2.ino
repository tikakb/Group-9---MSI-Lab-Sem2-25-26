const int relay1 = 7;
const int relay2 = 8;
const int trigPin = 9;
const int echoPin = 10;
const int ledPin = 11;

const int stopDistance = 10; 

void setup() {
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  stopActuator(); 
}

void loop() {
  int distance = getDistance();

  if (distance > 0 && distance <= stopDistance) {

    stopActuator();
    digitalWrite(ledPin, HIGH); 
  } else {
    
    digitalWrite(ledPin, LOW);
    
    
    extendActuator();
  }
  
  delay(100); 
}

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH, 30000); 
  return duration * 0.034 / 2;
}

void extendActuator() {
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
}

void stopActuator() {
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
}