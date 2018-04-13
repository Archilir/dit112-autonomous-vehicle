#include <AutonomousCarSystem.h>

//Car* car;
// Constructor
DriveController::DriveController()
{

}

void DriveController::begin(Car& newCar) {
  car = &newCar;
  init();
}

void DriveController::update() {
  //if (debugDriveController) debug("DriveController::update()");
  car->updateMotors();
}

void DriveController::init() {
  debugDriveController = true;
  if (debugDriveController) debug("DriveController::init()");
  car->enableCruiseControl();

}

void DriveController::drive() {
  if (debugDriveController) debug("DriveController::drive()");
  car->setSpeed(_MIN_CRUISE_CONTROL_SPEED);
}

void DriveController::reverse() {
  if (debugDriveController) debug("DriveController::reverse()");
  car->setSpeed(-_MIN_CRUISE_CONTROL_SPEED);
}

void DriveController::stop() {
  if (debugDriveController) debug("DriveController::stop()");
  car->setSpeed(0);
}

void DriveController::debug(String msg) {
  Serial.println(msg);
}
