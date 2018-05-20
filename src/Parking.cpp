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
    case _WAITING:     wait();     break;
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
  //driver  -> driveForward();
  driver -> drive(_MOVE_SPEED, 0);
  changeState(_SEARCHING);
}

void Parking::search() {
  bool test = sensors -> isSectorViable();
  if (test) {
    driver -> stop();
    driver -> disableDriftCorrection();
    delay(1000);
    parkingDirection = sensors -> getUnsyncAngularDisplacement();
    course = getNewDisplacement(parkingDirection, -45);

    //driver -> driveBackwardRight();
    driver -> drive(-_TURN_SPEED, _TURN_ANGLE);
    changeState(_ENTERING);
  }
  Serial.print(test);
  Serial.print('\t');
  Serial.print(sensors -> getOdometerLeftDistance());
  Serial.print('\t');
  Serial.println(sensors -> getOdometerRightDistance());

}

void Parking::enter() {
  if (withinRange(sensors -> getUnsyncAngularDisplacement(), lastDirection, course)) {
    //driver -> stop();
    //delay(500);
    //driver -> driveBackward();
    driver -> drive(-_MOVE_SPEED, 0);
    changeState(_BACKING);
    return;
  }

  if (sensors -> getDistanceMiddleSide() <= 5) {
    //driver -> driveBackward();
    if (driver -> getSpeed() != -_MOVE_SPEED) driver -> drive(-_MOVE_SPEED, 0);
  } else {
    //driver -> driveBackwardRight();
    if (driver -> getSpeed() != -_TURN_SPEED) driver -> drive(-_TURN_SPEED, _TURN_ANGLE);
  }
}

void Parking::back() {
  //sensors -> updateRearCorner();
  //if (sensors -> getDistanceRearCorner() > 0 && sensors -> getDistanceRearCorner() < 15)

  //  driver -> drive(driver -> getSpeed() - 5);
  if (sensors -> getDistanceRearCorner() < 14 ||
      sensors -> getDistanceRear()       < 10) {

    if (sensors -> getDistanceRearCorner() <= 5 ||
        sensors -> getDistanceRear()       <= 8) {
      //driver -> driveRight();
      driver -> drive(_TURN_SPEED,  _TURN_ANGLE);
    } else {
      //driver -> driveBackwardLeft();
      driver -> drive(-_TURN_SPEED, -_TURN_ANGLE);
    }
    changeState(_POSITIONING);
    return;
  }
}

void Parking::position() {
  if (withinRange(sensors -> getUnsyncAngularDisplacement(), lastDirection, parkingDirection)) {
    driver -> stop();
    changeState(_MEASURING);
    return;
  }
  if (sensors -> getSpeed() < 0) {
    if (sensors -> getDistanceRear()       <= 8 ||
        sensors -> getDistanceRearCorner() <= 5 ||
        sensors -> getDistanceMiddleSide() <= 5) {

      //driver -> stop();
      //delay(500);
      //driver -> driveForwardRight();
      driver -> drive(_TURN_SPEED, _TURN_ANGLE);
    }
  } else {
    if (sensors -> getDistanceFront() <= 7) {
      //driver -> stop();
      //delay(500);
      //driver -> driveBackwardLeft();
      driver -> drive(-_TURN_SPEED, -_TURN_ANGLE);
    }
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

void Parking::wait() {
  if (millis() >= timer)
    changeState(targetState);
}

void Parking::wait(char state, unsigned long delay) {
  timer = millis() + delay;
  targetState = state;
  changeState(_WAITING);
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

bool Parking::isParking() {
  driver -> disableAutonomy();
  return (parkingState == _IDLING) ? false : true;

}
