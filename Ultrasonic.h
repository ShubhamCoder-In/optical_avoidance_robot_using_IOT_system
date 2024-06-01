#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <Arduino.h>

class Ultrasonic {
  private:
    int trigPin;
    int echoPin;
    int thresholdDistance;
  public:
    Ultrasonic(int tPin, int ePin, int tdis);
    void setup();
    float getDistance();
    bool checkCollision();
};
#endif
