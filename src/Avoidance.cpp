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
  FirstMeasure = sensors -> getUnsyncAngularDisplacement();
  initialDegree = sensors -> getUnsyncAngularDisplacement();
  changeState(_firstTurn);
}
/*
void Avoidance::firstTurn() {
  driver -> setMotorSpeed(-turnSpeed,turnSpeed);
  if (initialDegree >= 90) {
    if (initialDegree == 90) {
      if (sensors -> getAngularDisplacement() < 200 &&
          sensors -> getAngularDisplacement() > 0) {
          driver -> stop();
          FirstMeasure = FirstMeasure - 90;
          changeState(_firstAdjust);
      }
    }
    if (sensors -> getAngularDisplacement() <= initialDegree - 90) {
      driver -> stop();
      FirstMeasure = FirstMeasure - 90;
      changeState(_firstAdjust);
    }
  } else {
    int negativeread = initialDegree - 90;
    if (sensors -> getAngularDisplacement() > 200 &&
        sensors -> getAngularDisplacement() <= 360-(-negativeread)) {
        car.setSpeed(0);
        FirstMeasure = 360-(-negativeread);
        changeState(_firstAdjust);
      }
    }
  }
}*/
