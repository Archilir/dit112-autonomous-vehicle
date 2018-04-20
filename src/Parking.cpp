#include <AutonomousCarSystem.h>

bool isReverseParking = false;
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

bool Parking::start(byte type) {
  if (!isParking()) {
    driver -> stop();
    driver -> setAutoControl();
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
  driver -> setManualControl();
  driver -> stop();
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

}

void Parking::reverseParking(){
  int initialDisplacement = sensors -> getAngularDisplacement();
  driver -> setAngle(45);
  driver -> setSpeed(-30);

  if(initialDisplacement - sensors -> getAngularDisplacement() == 45
  || (360 - sensors -> getAngularDisplacement()) + initialDisplacement == 45){
    driver -> setAngle(-45);
    isReverseParking = true;
  }
  if((sensors -> getAngularDisplacement() == initialDisplacement) && isReverseParking)
  {
    driver -> stop();
    isReverseParking = false;
  }
}
