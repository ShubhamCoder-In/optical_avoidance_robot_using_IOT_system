#ifndef SERVO_MOTOR_H
#define SERVO_MOTOR_H

#include <Arduino.h>
#include <Servo.h>
#include <EEPROM.h>

class ServoMotor {
  private:
    Servo servo;
    int pin;
    int referencePositionAddr;
    int referencePosition;

  public:
    ServoMotor(int servoPin, int refPosAddr);
    void setup();
    void move(int angle);
    void moveRight();
    void moveLeft();
    void moveReference();
};

#endif
