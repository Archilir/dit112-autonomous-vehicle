#include <AutonomousCarSystem.h>

void Sensors::begin(Car* reference) {
  car = reference;
  sonicBB.attach(_TRIGGER_PIN_FR, _ECHO_PIN_FR); //trigger pin, echo pin
  sonicBR.attach(_TRIGGER_PIN_BR, _ECHO_PIN_BR); //trigger pin, echo pin
  sonicFR.attach(_TRIGGER_PIN_BB, _ECHO_PIN_BB); //trigger pin, echo pin
  odometerLeft.attach(_ODOMETER_PIN_L);
  odometerRight.attach(_ODOMETER_PIN_R);
  gyro.attach();
  delay(1500);
  gyro.begin(60);
  odometerLeft.begin();
  odometerRight.begin();
  car->begin(odometerLeft, odometerRight, gyro);
  updateSensors();
  updateTimer = millis();
  disableMonitor();
}

void Sensors::update() {
  unsigned long timer = millis();
  if (timer >= 60 + updateTimer) {
    updateTimer = timer;
    updateSensors();
  }
  monitor();
}

void Sensors::updateSensors() {
    gyro.update();
    distanceFR = sonicFR.getMedianDistance(3);
    distanceBR = sonicBR.getMedianDistance(3);
    distanceBB = sonicBB.getMedianDistance(3);
    distanceL  = odometerLeft .getDistance();
    distanceR  = odometerRight.getDistance();
    gyroAngle  = gyro.getAngularDisplacement();
}

unsigned int Sensors::getDistanceFR()             { return distanceFR; }
unsigned int Sensors::getDistanceBR()             { return distanceBR; }
unsigned int Sensors::getDistanceBB()             { return distanceBB; }
unsigned int Sensors::getAngularDisplacement()    { return  gyroAngle; }

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
}

bool Sensors::isMonitoring()   {
  return monitoring;
}

void Sensors::resetMonitor() {
  lastSectorDepth  = 0;
  lastSectorLength = 0;
  sectorStart  = getOdometerAvgDistance();
  sectorEnd    = sectorStart;
  sectorDepth  = (distanceFR == 0) ? 70 : distanceFR;
}

void Sensors::monitor() {
  if (monitoring) {
    unsigned int currentDepth = (distanceFR == 0) ? 70 : distanceFR;

    int lBound = -3 + sectorDepth,
        rBound =  3 + sectorDepth;

    lBound = (lBound < 0) ? 0 : lBound;

    if (currentDepth <= lBound || currentDepth >= rBound) {
      lastSectorLength = sectorEnd - sectorStart;
      lastSectorDepth  = sectorDepth;
      sectorStart = sectorEnd;
      sectorDepth = currentDepth;
    }

    sectorEnd = getOdometerAvgDistance();
    if (currentDepth < sectorDepth) {
      sectorDepth = currentDepth;
    }
  }
}

bool Sensors::isSectorViable() {
  return (lastSectorLength > 40 && lastSectorDepth > 20) ? true : false;
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
