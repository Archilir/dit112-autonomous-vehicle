#include <AutonomousCarSystem.h>

// Constructor
Parking::Parking()
{

}

void Parking::begin (Driver* driverReference, Sensors* sensorsReference) {
  driver  = driverReference;
  sensors = sensorsReference;
}

bool Parking::isParking() {
  return (parkingState != _OFF) ? true : false;
}

bool Parking::start(char type) {
  if (!isParking()) {
    driver  -> setAutoControl();
    sensors -> startObstacleMonitor();
    switch (type) {
      case _PARALLEL:
        parkingState = _PARALLEL;
        driver -> driveSlow();
        break;

      default:
        driver -> setManualControl();
        return false;
        break;
    }

    return true;
  }

  return false;
}

void Parking::stop() {
  parkingState = _OFF;
  sensors -> stopObstacleMonitor();
  driver -> setManualControl();
}

void Parking::monitor() {
  if (isParking()) {
    switch (parkingState) {
      case _PARALLEL:
        parallel();
        break;

      default:
        break;
    }
  }
}

void Parking::parallel() {
  if (!targetFound) {
    if (sensors -> isObstacleUpdated()) {
        sensors -> obstacleDataUpdated = false;
        if (sensors -> getObstacleDistance() >= 30 &&
            sensors -> getObstacleMinDepth() >  10) {

            sensors -> stopObstacleMonitor();
            targetFound = true;
        }
    }
  } else {
    driver -> go(12);
    targetFound = false;
    stop();

  }
}
