#include <Arduino.h>
#include "L293D.h"
#include "Ultrasonic.h"
#include "ServoMotor.h"
#include "TriggeredCode.h"

// Constants and global variables
const int path[10] = {1,2,3,1,3,2};  // Define the path of movements
const int thresholdDistance = 10;  // Define the threshold distance for collision detection
int moveCount = 0;  // Initialize the move count
int currentCount = -1;  // Initialize the current move count
int currentPath = 0;  // Initialize the current path
bool collide = false;  // Initialize collision flag
bool Teststate = true;  // Initialize test state flag
int currentStage = 0;  // Initialize current stage
int nextPath = 0;  // Initialize next path
bool backwardMove = false;  // Initialize backward movement flag
int throwTime = 5000;  // Set the throw time
int servoPosition;  // Declare variable for servo position
unsigned long startTime = 0;  // Initialize start time
unsigned long endTime = 0;  // Initialize end time
unsigned long executionTime = 0;  // Initialize execution time
int movementduration = 0;  // Initialize movement duration
int sizeofarray = sizeof(path)/sizeof(path[0]);  // Calculate size of the path array
bool forwardMove = false;
bool throwError = false;
bool authorize = false;

// Objects
TriggeredCode triggeredCode;
L293D motor(3, 5, 6, 10, 2, 4);  // Define motor object with pin configuration
Ultrasonic sensor(11, 12, 10);  // Define ultrasonic sensor object with pin configuration
ServoMotor servo(9,0);  // Define servo motor object with pin and initial position

void setup(){
    Serial.begin(9600);
    motor.setup();  // Initialize motor
    sensor.setup();  // Initialize sensor
    servo.setup();  // Initialize servo
}

void loop(){
    if (triggeredCode.run()||authorize) {
      throwError = false;
      authorize = true;
        // Triggered code executed successfully, continue with main program logic
        Serial.println("Main program is running...");
        delay(1000); // Example delay
        
        // Check if the end of the path has been reached and no movement is in progress
        if (sizeofarray >= moveCount && movementduration == 0) {
            currentPath = path[moveCount];  // Update current path
        } 
        else{
          if(movementduration == 0){
          moveCount = 0;
          currentPath = path[moveCount]; 
          }
        }
        
        // Check if the move count has changed
        if (moveCount != currentCount) {
            currentCount = moveCount;  // Update current count
            switch(currentPath) {
                case 1:
                    servo.moveReference();  // Move servo to reference position
                    servoPosition = 90;  // Set servo position
                    if (!sensor.checkCollision()) {
                        startTime = millis();  // Record start time
                        motor.runTest(currentPath);  // Run motor test
                        forwardMove = true;
                    }
                    break;
                case 2:
                    servo.moveRight();  // Move servo right
                    servoPosition = 180;  // Set servo position
                    if (!sensor.checkCollision()) {
                        startTime = millis();  // Record start time
                        motor.runTest(currentPath);  // Run motor test
                    } else {
                        Teststate = false;  // Set test state to false
                    }
                    servo.moveReference();  // Move servo to reference position
                    break;
                case 3:
                    servo.moveLeft();  // Move servo left
                    servoPosition = 0;  // Set servo position
                    if (!sensor.checkCollision()) {
                        startTime = millis();  // Record start time
                        motor.runTest(currentPath);  // Run motor test
                    } else {
                        Teststate = false;  // Set test state to false
                    }
                    servo.moveReference();  // Move servo to reference position
                    break;
            }
            if(forwardMove){
              motor.runTest(1);
            }
        }
        // Check if execution time is within the throw time
        if (executionTime < throwTime) {
            endTime = millis();  // Record end time
            executionTime = executionTime + (endTime - startTime);  // Update execution time
            
            // Check for collision during movement and test state
            if (sensor.checkCollision() && !Teststate) {
                motor.runTest(5);  // Run motor test
                Teststate = false;  // Set test state to false
            }
            
            movementduration = throwTime - executionTime;  // Update movement duration
        } else {
            motor.runTest(5);  // Run motor test
            Serial.println(" movement change " + moveCount);
            moveCount++;  // Increment move count
            executionTime = 0;  // Reset execution time
            movementduration = 0;  // Reset movement duration
        }
        
        // Perform collision recovery if test state is false and movement duration is nonzero
        if (!Teststate && movementduration) {
            int checkAttempt = 3;
            for (int i = 0; i < 3; i++) {
                if (collide) {
                    switch (i) {
                        case 0:
                            servo.moveLeft();  // Move servo left
                            if (!sensor.checkCollision()) {
                                motor.runTest(3);  // Run motor test
                                collide = false;  // Reset collide flag
                            } else {
                                collide = true;  // Set collide flag
                            }
                            break;
                        case 1:
                            servo.moveRight();  // Move servo right
                            if (!sensor.checkCollision()) {
                                motor.runTest(2);  // Run motor test
                                collide = false;  // Reset collide flag
                            } else {
                                collide = true;  // Set collide flag
                            }
                            break;
                        case 3:
                            servo.moveReference();  // Move servo to reference position
                            if (collide) {
                                motor.runTest(4);  // Run motor test
                                if (!sensor.checkCollision()) {
                                    backwardMove = true;  // Set backward movement flag
                                    collide = false;  // Reset collide flag
                                } else {
                                    collide = true;  // Set collide flag
                                }
                            }
                            break;
                    } 
                    if (!collide) {
                        break;  // Exit loop if collision resolved
                    }
                }
            }
        }
        
        // Check if backward movement is required
        if (backwardMove) {
            // Move the servo to the reference position
            servo.moveReference();
            
            // Check for collision before proceeding
            if (!sensor.checkCollision()) {
                // If no collision, run the motor test (moving forward)
                motor.runTest(1);
                
                // Determine the next movement from the path
                nextPath = path[moveCount + 1];
                
                // Handle the next movement based on the path
                switch (nextPath) {
                    case 2:
                        // Move the servo to the left position
                        servo.moveLeft();
                        // Check for collision after moving left
                        if (!sensor.checkCollision()) {
                            // If no collision, run the motor test for moving backward
                            motor.runTest(3);
                            // Update the backward flag to false since backward movement is completed
                            backwardMove = false;
                        }
                        break;
                    case 3:
                        // Move the servo to the right position
                        servo.moveRight();
                        // Check for collision after moving right
                        if (!sensor.checkCollision()) {
                            // If no collision, run the motor test for moving backward
                            motor.runTest(2);
                            // Update the backward flag to false since backward movement is completed
                            backwardMove = false;
                        }
                        break;
                }
            }
        }
    } else {
         if(!throwError){
        // Triggered code was not executed successfully
        Serial.println("Triggered code failed to execute. Please retry.");
          throwError = true;
         }

    }
}
