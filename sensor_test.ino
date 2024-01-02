// Define sensor pins
const int forceSensorPin = A0;
const int joystickXPin = A1;
const int joystickYPin = A2;
const int potentiometerPin = A3;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Read values from sensors
  int forceSensorValue = analogRead(forceSensorPin);
  int joystickXValue = analogRead(joystickXPin);
  int joystickYValue = analogRead(joystickYPin);
  int potentiometerValue = analogRead(potentiometerPin);

  // Print sensor values to serial monitor
  Serial.print("Force Resistive Sensor: ");
  Serial.println(forceSensorValue);

  Serial.print("Joystick X: ");
  Serial.println(joystickXValue);

  Serial.print("Joystick Y: ");
  Serial.println(joystickYValue);

  Serial.print("Potentiometer: ");
  Serial.println(potentiometerValue);

  // Send data to serial plotter
  Serial.print("PLOT ");
  Serial.print(forceSensorValue);
  Serial.print(",");
  Serial.print(joystickXValue);
  Serial.print(",");
  Serial.print(joystickYValue);
  Serial.print(",");
  Serial.println(potentiometerValue);

  // Add a delay for readability
  delay(5);
}
