#include <AutonomousCarSystem.h>

void Sensors::begin(Car* reference) {
  car = reference;
  sonicFront.attach(_TRIGGER_PIN_FRONT, _ECHO_PIN_FRONT); //trigger pin, echo pin
  sonicRearCorner.attach(_TRIGGER_PIN_REAR_SIDE, _ECHO_PIN_REAR_SIDE); //trigger pin, echo pin
  sonicFrontSide.attach(_TRIGGER_PIN_FRONT_SIDE, _ECHO_PIN_FRONT_SIDE); //trigger pin, echo pin
  irMiddleSide.attach(_IR_PIN_MIDDLE_SIDE);
  odometerLeft.attach(_ODOMETER_PIN_L);
  odometerRight.attach(_ODOMETER_PIN_R);
  gyro.attach();
  delay(1500);
  gyro.begin(20);
  odometerLeft .begin();
  odometerRight.begin();
  car->begin(odometerLeft, odometerRight, gyro);
  pinMode(_SIREN_PIN, OUTPUT);
  updateSensors();
  updateTimer = millis();
}

void Sensors::update() {
  gyro.update();
  unsigned long timer = millis();
  if (timer >= 80 + updateTimer) {
    updateTimer = timer;
    updateSensors();
  }
  monitor();
}

void Sensors::updateSensors() {
    distanceFront      = sonicFront.getMedianDistance(3);
    distanceRearCorner = sonicRearCorner.getMedianDistance(3);
    distanceFrontSide  = sonicFrontSide.getMedianDistance(3);
    distanceMiddleSide = irMiddleSide.getMedianDistance(3);
    if (distanceMiddleSide == 0)
      distanceMiddleSide = 70;
    else if (distanceMiddleSide >= 12)
      distanceMiddleSide = distanceMiddleSide - 12;
    distanceL  = odometerLeft .getDistance();
    distanceR  = odometerRight.getDistance();
    gyroAngle  = gyro.getAngularDisplacement();
}

int Sensors::getSpeed() { return car -> getSpeed(); }

unsigned int Sensors::getDistanceFront()      { return distanceFront;      }
unsigned int Sensors::getDistanceFrontSide()  { return distanceFrontSide;  }
unsigned int Sensors::getDistanceRearCorner() { return distanceRearCorner; }
unsigned int Sensors::getDistanceMiddleSide() { return distanceMiddleSide; }

unsigned int Sensors::getAngularDisplacement()       { return  gyroAngle; }
unsigned int Sensors::getUnsyncAngularDisplacement() {
  return gyro.getAngularDisplacement();
}

unsigned long Sensors::getOdometerLeftDistance()  { return  distanceL; }
unsigned long Sensors::getOdometerRightDistance() { return  distanceR; }
unsigned long Sensors::getOdometerAvgDistance()
{
  return (distanceL + distanceR) / 2;
}

void Sensors::enableMonitor()  {
  if (!monitoring) {
    monitoring   = true;
    resetMonitor();
  }
}

void Sensors::disableMonitor() {
  monitoring = false;
  resetMonitor();
}

bool Sensors::isMonitoring()   {
  return monitoring;
}

void Sensors::resetMonitor() {
  sectorStart = getOdometerAvgDistance();
  sectorEnd   = sectorStart;
}

void Sensors::monitor() {
  if (monitoring) {
    unsigned int  currentDepth = (distanceMiddleSide == 0) ? 70 : distanceMiddleSide;
    if (currentDepth < 15) {
      sectorStart = getOdometerAvgDistance();
      sectorEnd   = sectorStart;
    } else {
      sectorEnd   = getOdometerAvgDistance();
    }
  }
}

bool Sensors::isSectorViable() {
  unsigned long distance = sectorEnd - sectorStart;
  return (distance >= 40) ? true : false;
}

bool Sensors::isClearSector() {
  unsigned long distance = sectorEnd - sectorStart;
  return (distance >= 100) ? true : false;
}

void Sensors::sirenOn() {
  analogWrite(_SIREN_PIN, 254);
}

void Sensors::sirenOff() {
  analogWrite(_SIREN_PIN, 0);
}

void Sensors::debug() {
  String sensorData = "F, FS, MS, RC, oL, oR, gyro:\t";
  sensorData += distanceFront;
  sensorData += "\t";
  sensorData += distanceFrontSide;
  sensorData += "\t";
  sensorData += distanceMiddleSide;
  sensorData += "\t";
  sensorData += distanceRearCorner;
  sensorData += "\t";
  sensorData += distanceL;
  sensorData += "\t";
  sensorData += distanceR;
  sensorData += "\t";
  sensorData += gyroAngle;
  Serial.println(sensorData);
}
