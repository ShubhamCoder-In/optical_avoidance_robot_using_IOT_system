#include "Ultrasonic.h"

Ultrasonic::Ultrasonic(int tPin, int ePin,int tdis) {
  trigPin = tPin;
  echoPin = ePin;
  thresholdDistance = tdis;
}

void Ultrasonic::setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

float Ultrasonic::getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  float duration = pulseIn(echoPin, HIGH);
  // Speed of sound: 343 m/s (34300 cm/s), so divide by 2 for one way distance
  // Formula: Distance = (duration * speed of sound) / 2
  return (duration * 0.0343) / 2; // Convert duration to cm
}
bool Ultrasonic::checkCollision() {
  int distanceToObject = getDistance(); // Get distance to object from sensor
  // Check if distance is less than the threshold for collision
  Serial.print(distanceToObject);
  return distanceToObject < thresholdDistance;
}