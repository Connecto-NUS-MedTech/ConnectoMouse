#include <ArduinoBLE.h>

const int fsrLeftPin = A0;
const int fsrRightPin = A1;
const int joystickXPin = A2;
const int joystickYPin = A3;
const int potentiometerPin = A4;

BLEService mouseService("1812");  // BLE Human Interface Device (HID) Service
BLECharacteristic mouseCharacteristic("2A4D", BLERead | BLEWrite, 2);  // BLE HID Report Characteristic

void setup() {
  Serial.begin(9600);

  if (!BLE.begin()) {
    Serial.println("Failed to initialize BLE!");
    while (1);
  }

  BLE.setLocalName("NanoMouse");
  BLE.setAdvertisedService(mouseService);
  mouseService.addCharacteristic(mouseCharacteristic);
  BLE.addService(mouseService);

  mouseCharacteristic.writeValue((const char*)0);  // Initial value

  BLE.advertise();

  Serial.println("NanoMouse BLE Peripheral - Waiting for connections...");
}

void loop() {
  int fsrLeftValue = analogRead(fsrLeftPin);
  int fsrRightValue = analogRead(fsrRightPin);
  int joystickXValue = analogRead(joystickXPin);
  int joystickYValue = analogRead(joystickYPin);
  int potentiometerValue = analogRead(potentiometerPin);

  // Format the data for the Serial Plotter
  Serial.print(fsrLeftValue);
  Serial.print("\t");
  Serial.print(fsrRightValue);
  Serial.print("\t");
  Serial.print(joystickXValue);
  Serial.print("\t");
  Serial.print(joystickYValue);
  Serial.print("\t");
  Serial.print(potentiometerValue);
  Serial.println();

  // Update the BLE characteristic value
  uint8_t potentiometerValueBytes[] = {static_cast<uint8_t>(potentiometerValue)};
  mouseCharacteristic.writeValue(potentiometerValueBytes, sizeof(potentiometerValueBytes));

  delay(50);
}
