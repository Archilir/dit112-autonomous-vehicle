#include <AutonomousCarSystem.h>


void Parking::begin (Driver* driverReference, Sensors* sensorsReference) {
  driver  = driverReference;
  sensors = sensorsReference;
}

void Parking::start() {
  parking = true;
  seeking = true;
  driver  -> disableTrackingCourse();
  driver  -> enableDriftCorrection();
  sensors -> enableMonitor();
  driver  -> driveForward();
//  sensors -> enableObstacleMonitor();
}

void Parking::stop() {
  driver  -> disableAutonomy();
  parking     = false;
  seeking     = false;
  maneuvering = false;
  positioning = false;
  isReverseParking = false;
  sensors -> disableMonitor();
}

void Parking::monitor() {
  if (parking) {
    if (seeking) {
      if (sensors -> isSectorViable()) {
        seeking = false;
        positioning = true;
      }
    } else if (positioning) {
      if (sensors -> isClearSector()) {
        stop();
      } else if (isPositioned()) {
        positioning = false;
        driver -> stop();
        delay(1000);
        parkingAlignment = sensors -> getUnsyncAngularDisplacement();
        maneuvering = true;
        previousFront = sensors -> getDistanceFR();
        previousBack  = sensors -> getDistanceBR();
        driver -> disableDriftCorrection();
        driver -> drive(-abs(driver -> getSpeed()), 60);
      }
    } else if (maneuvering) {
      reverseParking();
    } else {
      stop();
    }
  }
}

bool Parking::isPositioned() {
  return (sensors -> getDistanceBR() < 15) ? true : false;
}

int Parking::getNewDisplacement(int diff) {
  diff = parkingAlignment + diff;
  if (diff < 0)
    return 360 + diff;
  else if (diff > 360)
    return diff - 360;
  if (diff == 360) {
    diff = 0;
  }
  return diff;
}

int Parking::getShortestDisplacement(){
  unsigned int currentDisplacement = sensors -> getAngularDisplacement(),
               displacementL = parkingAlignment - currentDisplacement,
               displacementR = (360 - currentDisplacement) + parkingAlignment;

  if (displacementL == 360) displacementL = 0;
  if (displacementR == 360) displacementR = 0;

  if (displacementL < 0) displacementL = -displacementL;
  if (displacementL < displacementR)
    return displacementL;
  else
    return displacementR;
}



void Parking::reverseParking() {
  int shortestDisplacement = getShortestDisplacement();

  if (!isReverseParking) {
    if ((sensors -> getDistanceBR() > 0 && sensors -> getDistanceBR() < 10)) {
         Serial.println(sensors -> getDistanceBR());

    driver -> steer(0);
    }

    else if (shortestDisplacement <= 40 && !isReverseParking) {
      driver -> steer(60);
    }

    if (shortestDisplacement > 40 && shortestDisplacement <= 50) {
      isReverseParking = true;
      driver -> drive(-abs(driver -> getSpeed()), -60);
    }

    if (sensors -> getDistanceBB() > 0 &&
        sensors -> getDistanceBB() < 10) {

      isReverseParking = true;
      driver -> drive(abs(driver -> getSpeed()), 60);
    }
  }

  if (isReverseParking) {
    if (shortestDisplacement <= 3 || shortestDisplacement >= 357) {
      isReverseParking = false;
      maneuvering = false;
    }

    if (sensors -> getDistanceBB() >  0 && sensors -> getDistanceBB() <= 10) {
      driver -> drive(abs(driver -> getSpeed()), 60);
    }
  }
}

bool Parking::isViable(int current) {
  int m1 = getNewDisplacement(-5);
  int m2 = getNewDisplacement(5);
  if (m1 > m2) {
    if (m1 >= current && m2 <= current)
      return true;
  } else {
    if (m2 >= current && m1 <= current)
      return true;
  }
  return false;
}
