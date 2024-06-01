#ifndef L293D_H
#define L293D_H

#include <Arduino.h>

class L293D {
  private:
    int enablePin1;
    int in1;
    int in2;
    int enablePin2;
    int in3;
    int in4;

  public:
    L293D(int enPin1, int inPin1, int inPin2, int enPin2, int inPin3, int inPin4);
    void setup();
    void moveForward();
    void moveBackward();
    void turnLeft();
    void turnRight();
    void stop();
    void moveRightWheelForwardSlow();
    void moveRightWheelBackwardSlow();
    void moveLeftWheelForwardSlow();
    void moveLeftWheelBackwardSlow();
    void runTest(int movement);
};

#endif
