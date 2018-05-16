#include <AutonomousCarSystem.h>


void Parking::begin (Driver* driverReference, Sensors* sensorsReference) {
  driver  = driverReference;
  sensors = sensorsReference;
  lastDirection = sensors -> getAngularDisplacement();
}

/* Segment of the Activity loop responsible for monitoring the Parking module's
 * state machine's states.
 */

void Parking::monitor() {
  switch (parkingState) {
    case _IDLING:      idle();     break;
    case _STARTING:    start();    break;
    case _SEARCHING:   search();   break;
    case _ENTERING:    enter();    break;
    case _BACKING:     back();     break;
    case _POSITIONING: position(); break;
    case _MEASURING:   measure();  break;
    case _ALIGNING:    align();    break;
    case _STOPPING:    stop();     break;
  }
  lastDirection = sensors -> getAngularDisplacement();
}

/*
 * Dedicated method used for changing the states
 */

void Parking::changeState(char newState) {
  parkingState = newState;
}


unsigned int Parking::getNewDisplacement(int current, int diff) {
  diff = current + diff;
  if (diff < 0)
    return 360 + diff;
  else if (diff > 360)
    return diff - 360;
  if (diff == 360) {
    diff = 0;
  }
  return diff;
}

void Parking::idle() {
  // Serial.println("PARKING: idling.");
}

// PArking states

/* 1. Finding correct distance: SEARCH
 * 2. Turning 45o left while moving back: ENTER
 * 3. Backing 'till finding obstacle: BACK - Exit state: correct distance
 * 4. Turning 45o right before hitting course while moving forward: POSITION
 * 5. Calculating distance to front-back obstacles and finding a middle spot threshold: MEASURE
 * 6. Final positioning between obstacles: ALIGN
 */

// Initialize parking states

void Parking::initiate() {
  driver ->  enableAutonomy();
  changeState(_STARTING);

}

void Parking::start() {
  /*Serial.print(course);
  Serial.print('\t');
  Serial.print(sensors -> getAngularDisplacement());
  Serial.print('\t');
  Serial.println(getTarget(course, parkingDirection));*/

  parkingDirection = 0;
  course = 0;
  lastDirection = sensors -> getAngularDisplacement();
  driver  -> disableTrackingCourse();
  driver  -> enableDriftCorrection();
  sensors -> enableMonitor();
  driver  -> driveForward();
  changeState(_SEARCHING);
}


void Parking::search() {
  if (sensors -> isSectorViable()) {
    driver ->stop();
    delay(1000);
    parkingDirection = sensors -> getUnsyncAngularDisplacement();
    course = getNewDisplacement(parkingDirection, -45);
    driver -> disableDriftCorrection();
    driver -> driveBackwardRight();
    changeState(_ENTERING);
  }
}

void Parking::enter() {
  if (sensors -> getDistanceMiddleSide() < 5)
    driver -> driveBackward();
  else {
    driver -> driveBackwardRight();
  }

  if (withinRange(sensors -> getUnsyncAngularDisplacement(), lastDirection, course)) {
    driver -> driveBackward();
    changeState(_BACKING);
  }
}

void Parking::back() {
  if (sensors -> getDistanceRearCorner() < 12) {
    driver -> stop();
    delay(200);
    if (sensors -> getDistanceRearCorner() < 7)
      driver -> driveRight();
    else {
      driver -> driveBackwardLeft();
    }
    changeState(_POSITIONING);
  }
}

void Parking::position() {
  if (sensors -> getSpeed() < 0) {
    if (sensors -> getDistanceRearCorner() < 10 ||
        sensors -> getDistanceMiddleSide() < 5) {
      driver -> driveForward();
      delay(200);
      driver -> driveForwardRight();
    }
  } else {
    if (sensors -> getDistanceFront() < 6) {
      driver -> driveForward();
      delay(200);
      driver -> driveBackwardLeft();
    }
  }
  if (withinRange(sensors -> getUnsyncAngularDisplacement(), lastDirection, parkingDirection)) {
    driver -> driveForward();
    changeState(_MEASURING);
  }
}

void Parking::measure() {
  stop();
  //changeState(_ALIGNING);
}

void Parking::align() {

  changeState(_STOPPING);
}

void Parking::stop() {
  driver  -> disableAutonomy();
  sensors -> disableMonitor();
  changeState(_IDLING);
}

int Parking::getTarget(int x, int y) {
  return atan2(sin(x-y), cos(x-y));
}

bool Parking::withinRange(int min, int max, int target) {
  if (min > max) {
    int temp = max;
    max = min;
    min = temp;
  }

  if (max - min > 180) {
    if ((target >= 0 && target <= min) ||
        (target >= max && target <= 359))
        return true;
  } else {
      if (target >= min && target <= max)
        return true;
  }
  return false;
}
