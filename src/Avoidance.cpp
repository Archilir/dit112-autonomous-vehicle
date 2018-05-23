#include <AutonomousCarSystem.h>

void Avoidance::begin(Driver* driverReference, Sensors* sensorsReference) {
  driver  = driverReference;
  sensors = sensorsReference;
}

void Avoidance::changeState(char newState) {
  state = newState;
}

void Avoidance::inita() {
  driver -> stop();
  FirstMeasure  = sensors -> getAngularDisplacement();
  initialDegree = sensors -> getAngularDisplacement();
  changeState(_firstTurn);
}



void Avoidance::firstTurn() {

  driver -> setMotorSpeed(-turnSpeed,turnSpeed);
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
      FirstMeasure = FirstMeasure-90;
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
    driver -> setMotorSpeed(turnSpeed,-turnSpeed);
  }
  if (FirstMeasure<sensors -> getUnsyncAngularDisplacement()) {
    driver -> setMotorSpeed(-turnSpeed,turnSpeed);
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
  driver -> setMotorSpeed(turnSpeed,-turnSpeed);
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
  driver -> setMotorSpeed(turnSpeed,-turnSpeed);
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
  driver -> setMotorSpeed(-turnSpeed,turnSpeed);
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


void Avoidance::debug() {
  Serial.println(sensors -> getDistanceMiddleSide());
  Serial.println(initialDegree);
}


void Avoidance::takeRead() {
  FirstMeasure = sensors -> getUnsyncAngularDisplacement();
}

void Avoidance::monitor() {
  //debug();
  switch (state) {
    case _start       : inita();        break;
    case _firstTurn   : firstTurn();    break;
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

void Avoidance::startAvoidance() {
  driver -> enableAutonomy();
  changeState(_start);
}

void Avoidance::stopAvoidance() {
  driver -> disableAutonomy();
  changeState(_idle);

}

bool Avoidance::isEnabled() {
  if (state == _idle) {
    return true;
  } else {
    return false;
  }
}

// SonicA = Front
// SonicB = Front-Side
// SonicC = Rear
// IR     = Middle
