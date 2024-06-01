#include "TriggeredCode.h"

bool TriggeredCode::run() {
  int triggerPin;
  int timeout;

  // Wait for the trigger pin value (9870) to be entered
  while (Serial.available() > 0) {
    triggerPin = Serial.parseInt();
    if (triggerPin == 9870) {
      Serial.println("Trigger pin value received. Enter timeout value:");
      // Once the trigger pin value is received, proceed to get the timeout value
      while(Serial.available() == 0 );// Wait for input
      timeout = Serial.parseInt();
      Serial.print("Timeout value set to: ");
      Serial.println(timeout);
      // Your triggered code logic goes here
      Serial.println("Triggered code is running...");
      // Add a delay using the specified timeout
      delay(timeout);
      return true; // Return true indicating success
    } else {
      // If the entered value is not the trigger pin value, inform the user and wait for new input
      Serial.println("Incorrect trigger pin value. Enter the correct value to start the program:");
    }
  }
  return false; // Return false indicating failure (trigger pin value not entered correctly)
}
