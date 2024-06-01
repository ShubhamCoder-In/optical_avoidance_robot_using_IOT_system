#include <Servo.h>

#include "ServoMotor.h"

ServoMotor::ServoMotor(int servoPin, int refPosAddr) {
  pin = servoPin;
  referencePositionAddr = refPosAddr;
  int referencePosition = 90; // Default reference position
}

void ServoMotor::setup() {
  servo.attach(9);
  // Restore reference position from EEPROM
  
  referencePosition = EEPROM.read(referencePositionAddr);
  servo.write(referencePosition);
}

void ServoMotor::move(int angle) {
     if (angle >= 0 && angle <= 180) {
      servo.write(angle);
      referencePosition = angle; // Update reference position
      EEPROM.write(referencePositionAddr, referencePosition);
      Serial.println("Servo moved to the specified angle.");
    } else if (angle == -1) {
      servo.write(referencePosition); // Move servo to reference position
      Serial.println("Servo moved to reference position.");
    } else {
      Serial.println("Invalid angle. Please enter an angle between 0 and 180, or -1 to move to reference position.");
    }
    while (Serial.available() > 0) {
      Serial.read(); // Clear input buffer
    }
  }
void ServoMotor::moveLeft() {
  int leftAngle = 1; // Calculate the angle to move left
  move(leftAngle);
   delay(1000);
  Serial.println("......servo move left");
}

void ServoMotor::moveRight() {
  int rightAngle = 180; // Calculate the angle to move right
  move(rightAngle);
   delay(1000);
  Serial.println("###########servo move right");
}

void ServoMotor::moveReference() {
  servo.write(90);
  delay(1000);
  Serial.println("Servo moved to reference position.");
}
