#include <AutonomousCarSystem.h>

// Constructor
Driver::Driver()
{

}

void Driver::begin(Car* reference, Sensors* sensorRef) {
  car = reference;
  sensor = sensorRef;
  setManualControl();
}

bool Driver::isMoving() {
  return (car -> getSpeed() > 0 || car -> getSpeed() < 0) ? true : false;
}

bool Driver::isTurning(){
  return turningStatus;
}

void Driver::setTurning(bool value){
  turningStatus = value;
}

bool Driver::isAuto() {
  return car -> cruiseControlEnabled();
}

bool Driver::isManual() {
  return !isAuto();
}

void Driver::update() {
  if (isAuto())
    car -> updateMotors();

  //if (isMoving())
  //  driftCorrect();
}

void Driver::setManualControl() {
    car -> disableCruiseControl();
    stop();
    //clearDriftCorrectData();

  }
  void Driver::setAutoControl()   {
    stop();
    //clearDriftCorrectData();
    car -> enableCruiseControl();
  }


void Driver::stop() {
  //clearDriftCorrectData();
  //car -> stop();
  setSpeed(0);
}

void Driver::go(int cm) {
  car -> go(cm);
}

void Driver::clearDriftCorrectData(){
  onCourse = true;
  initialDisplacement = sensor -> getAngularDisplacement();
}

void Driver::setSpeed(int speed) { car -> setSpeed(speed); }
void Driver::drive(float speed)  { car -> setSpeed(speed); }

void Driver::driveSlow()         { drive( _MIN_CRUISE_SPEED); }
void Driver::driveAverage()      { drive( _AVG_CRUISE_SPEED); }
void Driver::driveFast()         { drive( _MAX_CRUISE_SPEED); }
void Driver::reverseSlow()       { drive(-_MIN_CRUISE_SPEED); }
void Driver::reverseAverage()    { drive(-_AVG_CRUISE_SPEED); }
void Driver::reverseFast()       { drive(-_MAX_CRUISE_SPEED); }

void Driver::setAngle(int angle) { car -> setAngle(angle); }
int Driver::getAngle() { return car -> getAngle(); }
int Driver::getSpeed() { return car -> getSpeed(); }

void Driver::driftCorrect(){
  if(isMoving() && !isTurning()){
    if(getAngle() == 0 && !onCourse){
      onCourse = true;
      initialDisplacement = sensor -> getAngularDisplacement();
      //Serial.println("reference offset set: ");
      //Serial.print(initialDisplacement);
    }

    else if(getAngle()==0 && initialDisplacement != sensor -> getAngularDisplacement()){
      //Serial.println("Drifting detected, correcting..");
      if(initialDisplacement>sensor -> getAngularDisplacement()){
        dRight = sensor -> getAngularDisplacement() - initialDisplacement;
        dLeft = 360-dRight;
      }
      else
      {
        dLeft = sensor -> getAngularDisplacement() - initialDisplacement;
        dRight = 360-dLeft;
      }

      if(dLeft<dRight)
      {
        setAngle(-45);
      }
      else
      {
        setAngle(45);
      }
      onCourse = false;
    }

    else if(getAngle()!=0 && initialDisplacement == sensor -> getAngularDisplacement())
    {
      //Serial.println("Drift corrected. Returning to previous state");
      onCourse = true;
      setAngle(0);
    }
  }

}
