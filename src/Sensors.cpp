#include <AutonomousCarSystem.h>

void Sensors::begin(Car* reference) {
  car = reference;
  sonicFront.attach(_TRIGGER_PIN_FRONT, _ECHO_PIN_FRONT); //trigger pin, echo pin
  sonicRear.attach(_TRIGGER_PIN_REAR, _ECHO_PIN_REAR); //trigger pin, echo pin
  sonicFrontSide.attach(_TRIGGER_PIN_FRONT_SIDE, _ECHO_PIN_FRONT_SIDE); //trigger pin, echo pin
  irMiddleSide.attach(_IR_PIN_MIDDLE_SIDE);
  irRearCorner.attach(_IR_PIN_REAR_CORNER);
  odometerLeft.attach(_ODOMETER_PIN_L);
  odometerRight.attach(_ODOMETER_PIN_R);
  gyro.attach();
  delay(1500);
  gyro.begin(16);
  odometerLeft .begin();
  odometerRight.begin();
  car->begin(odometerLeft, odometerRight, gyro);
  pinMode(_SIREN_PIN, OUTPUT);
  updateSensors();
  updateTimer = millis();
}

void Sensors::update() {
  if (sensorsEnabled) {
    gyro.update();
    unsigned long timer = millis();
    if (timer >= 80 + updateTimer) {
      updateTimer = timer;
      updateSensors();
    }
    monitor();
  }
}

void Sensors::enableSensors() {
  sensorsEnabled = true;
}

void Sensors::disableSensors() {
  sensorsEnabled = false;
}

bool Sensors::isEnabled() {
  return sensorsEnabled;
}

void Sensors::updateSensors() {
    distanceFront      = sonicFront.getMedianDistance(3);
    if (distanceFront == 0) distanceFront = 70;

    distanceRear       = sonicRear.getMedianDistance(3);
    if (distanceRear == 0) distanceRear = 70;

    distanceFrontSide  = sonicFrontSide.getMedianDistance(3);
    if (distanceFrontSide == 0) distanceFrontSide = 70;

    //distanceMiddleSide = irMiddleSide.getMedianDistance(3);
    distanceMiddleSide = irMiddleSide.getDistance();
    if (distanceMiddleSide == 0) distanceMiddleSide = 70;
    else if (distanceMiddleSide >= 12) distanceMiddleSide = distanceMiddleSide - 12;

    updateRearCorner();

    distanceL  = odometerLeft .getDistance();
    distanceR  = odometerRight.getDistance();
    gyroAngle  = gyro.getAngularDisplacement();
}

void Sensors::updateRearCorner() {
  distanceRearCorner   = irRearCorner.getDistance();
  //distanceRearCorner = irRearCorner.getMedianDistance(3);

  if (distanceRearCorner == 0)
    distanceRearCorner = 70;
  else if (distanceRearCorner >= 12)
    distanceRearCorner = distanceRearCorner - 12;
}

int Sensors::getSpeed() { return car -> getSpeed(); }

unsigned int Sensors::getDistanceFront()      { return distanceFront;      }
unsigned int Sensors::getDistanceFrontSide()  { return distanceFrontSide;  }
unsigned int Sensors::getDistanceRearCorner() { return distanceRearCorner; }
unsigned int Sensors::getDistanceRear()       { return distanceRear;       }
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

bool Sensors::passingObstacle() {
  unsigned long distance = sectorEnd - sectorStart;
  return (distance <= 1) ? true : false;
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
  String sensorData = "F, FS, MS, RC, R, oL, oR, gyro:\t";
  sensorData += distanceFront;
  sensorData += "\t";
  sensorData += distanceFrontSide;
  sensorData += "\t";
  sensorData += distanceMiddleSide;
  sensorData += "\t";
  sensorData += distanceRearCorner;
  sensorData += "\t";
  sensorData += distanceRear;
  sensorData += "\t";
  sensorData += distanceL;
  sensorData += "\t";
  sensorData += distanceR;
  sensorData += "\t";
  sensorData += gyroAngle;
  Serial.println(sensorData);
}
