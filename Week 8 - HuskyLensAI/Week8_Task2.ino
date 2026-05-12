#include "HUSKYLENS.h"
#include "SoftwareSerial.h"

HUSKYLENS huskylens;
SoftwareSerial mySerial(4, 5); // RX, TX

// DEFINE 
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600);
  
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // INITIAL LED OUTPUT
  setColor(0, 0, 0); 

  while (!huskylens.begin(mySerial)) {
    Serial.println(F("Begin failed!"));
    delay(500);
  }
  Serial.println("HuskyLens Ready!");
}

void loop() {
  if (!huskylens.request()) {
    setColor(0, 0, 0);
    return;
  }

  if (huskylens.available()) {
    HUSKYLENSResult result = huskylens.read();
    
    if (result.command == COMMAND_RETURN_BLOCK) {
      switch (result.ID) {
        case 1: // RED
          Serial.println("Color RED is detected");
          setColor(255, 0, 0);
          break;
        case 2: // BLUE
          Serial.println("Color BLUE is detected");
          setColor(0, 255, 0);
          break;
        case 3: // GREEN
          Serial.println("Color GREEN is detected");
          setColor(0, 0, 255);
          break;
        default:
          Serial.println("Unknown Color");
          setColor(0, 0, 0);
          break;
      }
    }
  } else {
    // NO COLOUR DETECTED
    setColor(0, 0, 0);
  }
}

// FUNCTION TO SET RGB COLOUR
void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}