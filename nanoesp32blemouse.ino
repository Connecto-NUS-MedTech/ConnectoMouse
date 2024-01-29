#include <BleConnectionStatus.h>
#include <BleMouse.h>

// Pins connected to sensors
const int fsrLeftPin = A0;
const int fsrRightPin = A1;
const int joystickXPin = A2;
const int joystickYPin = A3;

// BLEMouse object
BleMouse bleMouse;

void setup() {
  Serial.begin(115200);
  bleMouse.begin();
}

void loop() {
  // Read sensor values
  int fsrLeftValue = analogRead(fsrLeftPin);
  int fsrRightValue = analogRead(fsrRightPin);
  int joystickXValue = analogRead(joystickXPin);
  int joystickYValue = analogRead(joystickYPin);


  // Read joystick values and move the cursor
  int mappedJoystickX = map(joystickXValue, 1023, 4095, 5, -5);
  int mappedJoystickY = map(joystickYValue, 1023, 4095, -5, 5);
  bleMouse.move(mappedJoystickX, mappedJoystickY, 0);

  // Handle left click
  if (fsrLeftValue > 2000) {
    bleMouse.press(MOUSE_LEFT);
  } else {
    bleMouse.release(MOUSE_LEFT);
  }

  // Handle right click
  if (fsrRightValue > 2000) {
    bleMouse.press(MOUSE_RIGHT);
  } else {
    bleMouse.release(MOUSE_RIGHT);
  }

  delay(10); // Adjust the delay based on your requirements
}