#include <AutonomousCarSystem.h>

SR04 sonicFR, sonicBR, sonicBB;
Odometer odometerLeft(188), odometerRight(188);

Gyroscope gyro(22);

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
  gyro.update();        // gyro value stored in Smartshield
  updateUltrasonic();   // manual update and storage for synchronisity

}

void Sensors::updateUltrasonic() {
  // 20 milliseconds each
  //sonicFRDistance = sonicFR.getMedianDistance();
  //sonicBRDistance = sonicBR.getMedianDistance();
  //sonicBBDistance = sonicBB.getMedianDistance();
}

int Sensors::getFRDistance() { return sonicFR.getDistance(); }
int Sensors::getBRDistance() { return sonicBR.getDistance(); }
int Sensors::getBBDistance() { return sonicBB.getDistance(); }
int Sensors::getFRMedian()   { return sonicFR.getMedianDistance(); }
int Sensors::getBRMedian()   { return sonicBR.getMedianDistance(); }
int Sensors::getBBMedian()   { return sonicBB.getMedianDistance(); }


void Sensors::enableObstacleMonitor() {
  obstacleMonitorState = true;
}

void Sensors::disableObstacleMonitor() {
  obstacleMonitorState = false;
}

bool Sensors::obstacleMonitorEnabled() {
  return obstacleMonitorState;
}

void Sensors::startObstacleMonitor() {
  enableObstacleMonitor();
  lastDepth = getFRMedian();
  minDepth = (lastDepth == 0) ? 70 : lastDepth;
  startPos = odometerLeft.getDistance();
  lastEndPos = startPos;
}

void Sensors::stopObstacleMonitor() {
  disableObstacleMonitor();
}

bool Sensors::isObstacleUpdated() {
  return obstacleDataUpdated;
}

int Sensors::getObstacleDistance() {
  return obstacleDistance;
}

int Sensors::getObstacleMinDepth() {
  return obstacleMinDepth;
}

void Sensors::obstacleMonitor() {
  if (obstacleMonitorEnabled()) {
    int currentDepth = getFRMedian();
    currentDepth = (currentDepth == 0) ? 70 : currentDepth;
    endPos = odometerLeft.getDistance();


    int lBound = -_OBSTACLE_SENSITIVITY_THRESHOLD + lastDepth,
        rBound =  _OBSTACLE_SENSITIVITY_THRESHOLD + lastDepth;
    lBound = (lBound < 0) ? 0 : lBound;

    if (currentDepth <= lBound || currentDepth >= rBound) {
      obstacleDistance = lastEndPos - startPos;
      obstacleMinDepth = minDepth;
      startPos = endPos;
      obstacleDataUpdated = true;
      minDepth = (currentDepth == 0) ? 70 : currentDepth;
    }
      lastEndPos = endPos;
      minDepth   = (currentDepth < minDepth) ? currentDepth : minDepth;
      lastDepth = currentDepth;
  }
}

long Sensors::getAngularDisplacement() {
  return gyro.getAngularDisplacement();
}

void Sensors::debug() {
  String sensorData = "FR, BR, BB, oL, oR, gyro: ";
  sensorData += sonicFRDistance;
  sensorData += "\t";
  sensorData += sonicBRDistance;
  sensorData += "\t";
  sensorData += sonicBBDistance;
  sensorData += "\t";
  sensorData += odometerLeft.getDistance();
  sensorData += "\t";
  sensorData += odometerRight.getDistance();
  sensorData += "\t";
  sensorData += gyro.getAngularDisplacement();
  Serial.println(sensorData);
}
