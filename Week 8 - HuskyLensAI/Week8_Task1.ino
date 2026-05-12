#include "HUSKYLENS.h"
#include "SoftwareSerial.h"

HUSKYLENS huskylens;
SoftwareSerial mySerial(4, 5); // RX, TX

const int LED1 = 8;

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600);
  
  pinMode(LED1,OUTPUT); 
  // Wait for HuskyLens to connect
  while (!huskylens.begin(mySerial)) {
    Serial.println(F("Begin failed! Check wiring and Protocol (Serial 9600)"));
    delay(500);
  }
  Serial.println("HuskyLens Ready!");
}

void loop() {
  if (!huskylens.request()) return; // Skip loop if no data
  
  // If the camera sees a trained object
  if (huskylens.available()) {
    HUSKYLENSResult result = huskylens.read();
    
    // Check if the result is a standard object block
    if (result.command == COMMAND_RETURN_BLOCK && result.ID == 1) {
      Serial.print("Object ");
      Serial.print(result.ID);
      Serial.println(" detected!");
      digitalWrite(LED1,HIGH);
      }
    else {
      Serial.println("No Object Detected!");
      digitalWrite(LED1,LOW);
      }
    
  }
}