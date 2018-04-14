#include <AutonomousCarSystem.h>


// Constructor
Driver::Driver()
{

}

void Driver::begin(Car* reference) {
  car = reference;
  setManualControl();
}

bool Driver::isMoving() {
  return (car -> getSpeed() > 0 || car -> getSpeed() < 0) ? true : false;
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
}

void Driver::setManualControl() {
  stop();
  car -> disableCruiseControl();
}
void Driver::setAutoControl()   {
  stop();
  car -> enableCruiseControl();
}

void Driver::stop() {
  car -> stop();
}

void Driver::go(int cm) {
  car -> go(cm);
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
