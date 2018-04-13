#include <ACS.h>

SR04 sonicFR, sonicBR, sonicBB;
Odometer odometerLeft(188), odometerRight(188);

Gyroscope gyro(25);

// Constructor
SensorBridge::SensorBridge()
{

}

void SensorBridge::begin(Car& newCar) {
  car = &newCar;
  init();
}

void SensorBridge::init()
{
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

long SensorBridge::getOdometerLeftDistance() {
  return odometerLeft.getDistance();
}

long SensorBridge::getOdometerRightDistance() {
  return odometerRight.getDistance();
}

void SensorBridge::update() {
  gyro.update();
}

void SensorBridge::debug() {
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
