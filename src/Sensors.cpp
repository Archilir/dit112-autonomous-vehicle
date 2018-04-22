#include <AutonomousCarSystem.h>

SR04 sonicFR, sonicBR, sonicBB;
Odometer odometerLeft(188), odometerRight(188);

Gyroscope gyro(25);

// Constructor
Sensors::Sensors()
{

}

void Sensors::begin(Car* reference) {
  car = reference;
  sonicBB.attach(_TRIGGER_PIN_FR, _ECHO_PIN_FR); //trigger pin, echo pin
  sonicBR.attach(_TRIGGER_PIN_BR, _ECHO_PIN_BR); //trigger pin, echo pin
  sonicFR.attach(_TRIGGER_PIN_BB, _ECHO_PIN_BB); //trigger pin, echo pin
  odometerLeft.attach(_ODOMETER_PIN_L);
  odometerRight.attach(_ODOMETER_PIN_R);
  gyro.attach();
  delay(1500);
  gyro.begin(90);
  odometerLeft.begin();
  odometerRight.begin();
  car->begin(odometerLeft, odometerRight, gyro);
}

// GETTERS

long Sensors::getOdometerLeftDistance() {
  return odometerLeft.getDistance();
}

long Sensors::getOdometerRightDistance() {
  return odometerRight.getDistance();
}

void Sensors::update() {
  gyro.update();
}

long Sensors::getAngularDisplacement() {
  return gyro.getAngularDisplacement();
}

void Sensors::debug() {
  String sensorData = "FR, BR, BB, oL, oR, gyro: ";
  sensorData += sonicFR.getDistance();
  sensorData += "\t";
  sensorData += sonicBR.getDistance();
  sensorData += "\t";
  sensorData += sonicBB.getDistance();
  sensorData += "\t";
  sensorData += odometerLeft.getDistance();
  sensorData += "\t";
  sensorData += odometerRight.getDistance();
  sensorData += "\t";
  sensorData += gyro.getAngularDisplacement();
  Serial.println(sensorData);
}

long Sensors::getFRDistance(){
  return sonicFR.getDistance();
}

long Sensors::getBRDistance(){
  return sonicBR.getDistance();
}

long Sensors::getBBDistance(){
  return sonicBB.getDistance();
}

long Sensors::getBBMedian() {
  return sonicBB.getMedianDistance();
}
