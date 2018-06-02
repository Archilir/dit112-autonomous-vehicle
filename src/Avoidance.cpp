#include <AutonomousCarSystem.h>

void Avoidance::begin(Driver* driverReference, Sensors* sensorsReference) {
  driver  = driverReference;
  sensors = sensorsReference;
}

void Avoidance::startAvoidance() {
  driver -> enableAutonomy();
  changeState(_start);
}

void Avoidance::stopAvoidance() {
  driver -> disableAutonomy();
  changeState(_idle);
}

bool Avoidance::isEnabled() {
  return (state == _idle) ? true : false;
}

void Avoidance::changeState(char newState) {
  state = newState;
}

/*int Avoidance::getTurnDirection(int targetDegrees) {
  targetDegrees %= 360;
  return (targetDegrees > 0) ? 1 : -1;
}*/



void Avoidance::debug() {
  Serial.println(sensors -> getDistanceMiddleSide());
  Serial.println(initialDegree);
}

void Avoidance::monitor() {
  //debug();
  switch (state) {
    /*
    case _INIT         : init();              break;
    case _FIRST_MOVE   : firstMove();         break;
    case _CALCULATE    : calculateRotation(); break;
    case _TRACK_ROTATE : trackRotation();     break;
    case _MOVE         : moveVehicle();              break;
    */
    case _start       : inita();         break;
    case _firstTurn   : firstTurn();     break;


    case _thirdTurn   : thirdTurn();    break;
    case _firstGo     : firstGo();      break;
    case _firstAdjust : firstAdjust();  break;
    case _secondGoPT  : secondGoPT();   break;
    case _secondGo    : secondGo();     break;
    case _secondTurn  : secondTurn();   break;
    case _thirdAdjust : thirdAdjust();  break;
    case _finish      : finish();       break;
    case _jesus       : christ();       break;
    case _secondAdjust: secondAdjust(); break;
  }
}

/*
void Car::initiate() {
  targetDegrees = 0;
  degreesTurnedSoFar = 0;
  initialHeading = sensors -> getUnsyncAngularDisplacement();
  rotationHeading = 0;
  driver -> enableAutonomy();
  changeState(_FIRST_MOVE);
}

void Car::firstMove() {
  if (sensors -> getDistanceFront() < 10 &&
      sensors -> getDistanceFrontSide() < 10)
      driver -> stop();
      delay(500);
      targetDegrees = -90;
      changeState(_CALCULATE);
  else if (sensors -> getDistanceFront() < 10)
      setMotorSpeed(0, 0);
  else
    setMotorSpeed(_MOVE_SPEED, _MOVE_SPEED);
}

void Car::calculateRotation(){
    targetDegrees %= 360;
    rotationHeading = sensors -> getUnsyncAngularDisplacement();
    degreesTurnedSoFar = 0;
    if (targetDegrees > 0){
        setMotorSpeed(_TURN_SPEED, -_TURN_SPEED);
    } else {
        setMotorSpeed(-_TURN_SPEED, _TURN_SPEED);
    }
    changeState(_TRACK_ROTATE);
}

void Car::trackRotation() {
   if (abs(degreesTurnedSoFar) < abs(targetDegrees)) {
      int currentHeading = sensors -> getUnsyncAngularDisplacement();
      if (targetDegrees < 0 && currentHeading > rotationHeading){
              currentHeading -= 360;
      }else if (targetDegrees > 0 && currentHeading < rotationHeading){
              currentHeading += 360;
      }
      degreesTurnedSoFar = rotationHeading - currentHeading;
  } else {
  driver -> stop();
  degreesTurnedSoFar = 0;
  targetDegrees = 0;
  initialHeading = 0;
  delay(500);
  setMotorSpeed(_MOVE_SPEED, _MOVE_SPEED);
  changeState(_MOVE);
  }
}

void Car::moveVehicle() {
  driver -> drive(forwardSpeed);
  if (sensors -> getDistanceFront() < 10 &&
      sensors -> getDistanceFrontSide() < 10 &&
      sensors -> getDistanceMiddleSide() < 10)
      driver -> stop();
      delay(500);
      targetDegrees = ;
      finalManeuver = true;
      changeState(_)
  if (sensors -> getDistanceMiddleSide() >= 15) {

    driver -> stop();
    delay(500);
    changeState(_secondTurn);

  }
}*/

void Avoidance::inita() {
  driver -> stop();
  FirstMeasure  = sensors -> getAngularDisplacement();
  initialDegree = sensors -> getAngularDisplacement();
  changeState(_firstTurn);
}

void Avoidance::firstTurn() {

  driver -> setMotorSpeed(-_TURN_SPEED,_TURN_SPEED);
  if (initialDegree >= 90) {
    if (initialDegree == 90 &&
        sensors -> getUnsyncAngularDisplacement()<200 &&
        sensors -> getUnsyncAngularDisplacement()>0) {
          driver -> stop();
          FirstMeasure = FirstMeasure-90;
          changeState(_firstAdjust);
    }
    if (sensors -> getUnsyncAngularDisplacement() <= initialDegree - 90) {
      driver -> stop();
      FirstMeasure = FirstMeasure -90;
      changeState(_firstAdjust);
    }
  }
  else {
    int negativeread = initialDegree-90;
    if (sensors -> getUnsyncAngularDisplacement() >  200 &&
        sensors -> getUnsyncAngularDisplacement() <= 360-(-negativeread)) {
          driver -> stop();
          FirstMeasure = 360-(-negativeread);
          changeState(_firstAdjust);
    }
  }
}

void Avoidance::firstAdjust() {
  if (FirstMeasure>sensors -> getUnsyncAngularDisplacement()) {
    driver -> setMotorSpeed(_TURN_SPEED,-_TURN_SPEED);
  }
  if (FirstMeasure<sensors -> getUnsyncAngularDisplacement()) {
    driver -> setMotorSpeed(-_TURN_SPEED,_TURN_SPEED);
  }
  if (FirstMeasure == sensors -> getUnsyncAngularDisplacement()     ||
      FirstMeasure == sensors -> getUnsyncAngularDisplacement() + 1 ||
      FirstMeasure == sensors -> getUnsyncAngularDisplacement() - 1 ) {
        driver -> stop();
        changeState(_firstGo);
  }

}

void Avoidance::firstGo(){
  driver -> drive(forwardSpeed);
  if (sensors -> getDistanceMiddleSide() >= 15) {

    driver -> stop();
    changeState(_secondTurn);

  }

}

void Avoidance::secondTurn() {
  driver -> setMotorSpeed(_TURN_SPEED,-_TURN_SPEED);
  if (initialDegree <= 90 &&
      sensors -> getUnsyncAngularDisplacement() < 200 &&
      sensors -> getUnsyncAngularDisplacement() > initialDegree) {
        driver -> stop();
        secondAdjustint = sensors -> getUnsyncAngularDisplacement();
        changeState(_secondAdjust);
  }

  else if (sensors -> getUnsyncAngularDisplacement()>FirstMeasure) {
    driver -> stop();
    secondAdjustint = sensors -> getUnsyncAngularDisplacement();
    changeState(_secondAdjust);
  }
}

void Avoidance::secondAdjust() {
  if (secondAdjustint>sensors -> getUnsyncAngularDisplacement()) {
    driver -> setMotorSpeed(adjustSpeed,-adjustSpeed);
  }
  if (secondAdjustint<sensors -> getUnsyncAngularDisplacement()) {
    driver -> setMotorSpeed(-adjustSpeed,adjustSpeed);
  }
  if (secondAdjustint == sensors -> getUnsyncAngularDisplacement()     ||
      secondAdjustint == sensors -> getUnsyncAngularDisplacement() + 1 ||
      secondAdjustint == sensors -> getUnsyncAngularDisplacement() - 1 ||
      secondAdjustint == sensors -> getUnsyncAngularDisplacement() - 2 ) {
        driver -> stop();
        changeState(_secondGo);
  }

}

void Avoidance::secondGo() {
  if (sensors -> getDistanceMiddleSide() >= 15) {
        driver -> drive(forwardSpeed);
  }
  else {
    changeState(_secondGoPT);
  }
}

void Avoidance::secondGoPT() {
  driver -> drive(forwardSpeed);
  if (sensors -> getDistanceMiddleSide() >=15) {
    driver -> stop();
    changeState(_thirdTurn);
  }
}

void Avoidance::thirdTurn() {
  driver -> setMotorSpeed(_TURN_SPEED,-_TURN_SPEED);
  if (initialDegree<270) {
    FirstMeasure = initialDegree+90;
  }
  else {
    FirstMeasure = initialDegree+90-360;
  }
  if (initialDegree<=90 &&
      sensors -> getUnsyncAngularDisplacement()<200 &&
      sensors -> getUnsyncAngularDisplacement()>FirstMeasure) {
        driver -> stop();
        changeState(_thirdAdjust);
  }
  else if (sensors -> getUnsyncAngularDisplacement()>FirstMeasure) {
    driver -> stop();
    changeState(_thirdAdjust);
  }
}

void Avoidance::thirdAdjust() {
  if (FirstMeasure>sensors -> getUnsyncAngularDisplacement()) {
    driver -> setMotorSpeed(adjustSpeed,-adjustSpeed);
  }
  if (FirstMeasure<sensors -> getUnsyncAngularDisplacement()) {
    driver -> setMotorSpeed(-adjustSpeed,adjustSpeed);
  }
  if (FirstMeasure == sensors -> getUnsyncAngularDisplacement()     ||
      FirstMeasure == sensors -> getUnsyncAngularDisplacement() + 1 ||
      FirstMeasure == sensors -> getUnsyncAngularDisplacement() - 1 ||
      FirstMeasure == sensors -> getUnsyncAngularDisplacement() - 2) {
        driver -> stop();
        changeState(_jesus);
  }
 }

void Avoidance::christ() {
  driver -> drive(forwardSpeed);
  if (sensors -> getDistanceFront() <= 10) {
    driver -> stop();
    changeState(_finish);
  }
}

void Avoidance::finish() {
  driver -> setMotorSpeed(-_TURN_SPEED,_TURN_SPEED);
  if (FirstMeasure==90 &&
      sensors -> getUnsyncAngularDisplacement()>200 &&
      sensors -> getUnsyncAngularDisplacement()>initialDegree) {
        driver -> stop();
        FirstMeasure = FirstMeasure-90;
        changeState(_idle);
  }

  if (sensors -> getUnsyncAngularDisplacement() <= initialDegree) {
    driver -> stop();
    changeState(_idle);
  }
}

void Avoidance::takeRead() {
  FirstMeasure = sensors -> getUnsyncAngularDisplacement();
}

// SonicA = Front
// SonicB = Front-Side
// SonicC = Rear
// IR     = Middle
