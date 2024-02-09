#include <BleConnectionStatus.h>
#include <BleMouse.h>

// Pins connected to sensors
const int fsrLeftPin1 = A0;
const int fsrRightPin1 = A1;
const int joystickXPin = A2;
const int joystickYPin = A3;
const int potentiometerPin = A4;
const int fsrLeftPin2 = A5;
const int fsrRightPin2 = A6;

// BLEMouse object
BleMouse bleMouse;

void setup() {
  Serial.begin(115200);
  bleMouse.begin();
}

void loop() {
  // Read sensor values
  int fsrLeftValue1 = analogRead(fsrLeftPin1);
  int fsrRightValue1 = analogRead(fsrRightPin1);
  int joystickXValue = analogRead(joystickXPin);
  int joystickYValue = analogRead(joystickYPin);
  int potentiometerValue = analogRead(potentiometerPin);
  int fsrLeftValue2 = analogRead(fsrLeftPin2);
  int fsrRightValue2 = analogRead(fsrRightPin2);
  int ValueA = -4;
  int ValueB = 4;
  int ValueC = 4;
  int ValueD = -4;

  if (potentiometerValue == 1023) {
    ValueA = -4;
    ValueB = 4;
    ValueC = 4;
    ValueD = -4;
  } else {
    ValueA = 4;
    ValueB = -4;
    ValueC = 4;
    ValueD = 4;
  }

  // Read joystick values and move the cursor
  int mappedJoystickX = map(joystickXValue, 1023, 4095, ValueA, ValueB);
  int mappedJoystickY = map(joystickYValue, 1023, 4095, ValueC, ValueD);
  bleMouse.move(mappedJoystickX, mappedJoystickY, 0);

  // Handle left click
  if (((fsrLeftValue1 > 2000 && potentiometerValue == 1023) || fsrLeftValue2 > 2000) && potentiometerValue == 0) {
      bleMouse.press(MOUSE_LEFT);
    } else {
      bleMouse.release(MOUSE_LEFT);
    }

  // Handle right click
  if (((fsrRightValue1 > 2000 && potentiometerValue == 1023) || fsrRightValue2 > 2000) && potentiometerValue == 0) {
      bleMouse.press(MOUSE_RIGHT);
    } else {
      bleMouse.release(MOUSE_RIGHT);
    }
  

  delay(10); // Adjust the delay based on your requirements
}
