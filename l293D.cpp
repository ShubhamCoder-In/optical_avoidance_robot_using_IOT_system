#include "L293D.h"

L293D::L293D(int enPin1, int inPin1, int inPin2, int enPin2, int inPin3, int inPin4) {
  enablePin1 = enPin1;
  in1 = inPin1;
  in2 = inPin2;
  enablePin2 = enPin2;
  in3 = inPin3;
  in4 = inPin4;
}

void L293D::setup() {
  pinMode(enablePin1, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enablePin2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  stop();
}

void L293D::moveForward() {
  stop(); // Ensure both wheels are stopped before moving
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  digitalWrite(enablePin1, HIGH);
  digitalWrite(enablePin2, HIGH);
}

void L293D::moveBackward() {
  stop(); // Ensure both wheels are stopped before moving
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  digitalWrite(enablePin1, HIGH);
  digitalWrite(enablePin2, HIGH);
  delay(2000);
  stop();
}

void L293D::turnLeft() {
  stop(); // Ensure both wheels are stopped before moving
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  digitalWrite(enablePin1, HIGH);
  digitalWrite(enablePin2, HIGH);
  delay(1000);
}

void L293D::turnRight() {
  stop(); // Ensure both wheels are stopped before moving
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(enablePin1, HIGH);
  digitalWrite(enablePin2, HIGH);
  delay(1000);
}

void L293D::stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(enablePin1, LOW);
  digitalWrite(enablePin2, LOW);
}

void L293D::moveRightWheelForwardSlow() {
  stop(); // Ensure both wheels are stopped before moving
  analogWrite(enablePin1, 200); // Adjust the PWM value for slower speed 
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  delay(2000);
}

void L293D::moveRightWheelBackwardSlow() {
  stop(); // Ensure both wheels are stopped before moving
  analogWrite(enablePin1, 200); // Adjust the PWM value for slower speed
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  delay(2000);
}

void L293D::moveLeftWheelForwardSlow() {
  stop(); // Ensure both wheels are stopped before moving
  analogWrite(enablePin2, 200); // Adjust the PWM value for slower speed
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(2000);
}

void L293D::moveLeftWheelBackwardSlow() {
  stop(); // Ensure both wheels are stopped before moving
  analogWrite(enablePin2, 200); // Adjust the PWM value for slower speed
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(2000);
}
void L293D::runTest(int movement) {
  switch (movement) {
    case 1:
      moveForward();
      Serial.println("Moving forward");
      break;
    case 2:
      turnRight();
      Serial.println("Turning right");
      break;
    case 3:
      turnLeft();
      Serial.println("Turning left");
      break;
    case 4:
      moveBackward();
      Serial.println("Moving backward");
      break;
    case 5:
      stop();
      Serial.println("Stopping");
      break;
    case 6:
      moveRightWheelForwardSlow();
      Serial.println("Moving right wheel forward slowly");
      break;
    case 7:
      moveRightWheelBackwardSlow();
      Serial.println("Moving right wheel backward slowly");
      break;
    case 8:
      moveLeftWheelForwardSlow();
      Serial.println("Moving left wheel forward slowly");
      break;
    case 9:
      moveLeftWheelBackwardSlow();
      Serial.println("Moving left wheel backward slowly");
      break;
    default:
      Serial.println("Invalid movement");
  }
}