#include <AutonomousCarSystem.h>

void Sensors::begin(Car* reference) {
  car = reference;
  sonicBB.attach(_TRIGGER_PIN_BB, _ECHO_PIN_BB); //trigger pin, echo pin
  sonicBR.attach(_TRIGGER_PIN_BR, _ECHO_PIN_BR); //trigger pin, echo pin
  sonicFR.attach(_TRIGGER_PIN_FR, _ECHO_PIN_FR); //trigger pin, echo pin
  odometerLeft.attach(_ODOMETER_PIN_L);
  odometerRight.attach(_ODOMETER_PIN_R);
  gyro.attach();
  delay(1500);
  gyro.begin(20);
  odometerLeft.begin();
  odometerRight.begin();
  car->begin(odometerLeft, odometerRight, gyro);
  updateSensors();
  updateTimer = millis();
}

void Sensors::update() {
  gyro.update();
  unsigned long timer = millis();
  if (timer >= 60 + updateTimer) {
    updateTimer = timer;
    updateSensors();
  }
  monitor();
}

void Sensors::updateSensors() {
    distanceFR = sonicFR.getMedianDistance(3);
    distanceBR = sonicBR.getMedianDistance(3);
    distanceBB = sonicBB.getMedianDistance(3);
    distanceL  = odometerLeft .getDistance();
    distanceR  = odometerRight.getDistance();
    gyroAngle  = gyro.getAngularDisplacement();
}

unsigned int Sensors::getDistanceFR()                { return distanceFR; }
unsigned int Sensors::getDistanceBR()                { return distanceBR; }
unsigned int Sensors::getDistanceBB()                { return distanceBB; }
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
    unsigned int  currentDepth = (distanceBR == 0) ? 70 : distanceBR;
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

void Sensors::debug() {
  String sensorData = "FR, BR, BB, oL, oR, gyro: ";
  sensorData += distanceFR;
  sensorData += "\t";
  sensorData += distanceBR;
  sensorData += "\t";
  sensorData += distanceBB;
  sensorData += "\t";
  sensorData += distanceL;
  sensorData += "\t";
  sensorData += distanceR;
  sensorData += "\t";
  sensorData += gyroAngle;
  Serial.println(sensorData);
}
