#include <AutonomousCarSystem.h>

bool isReverseParking = false;
int initialDisplacement;
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
int Parking::getShortestDisplacement(){
  int currentDisplacement = sensors -> getAngularDisplacement();
  int displacement1 = initialDisplacement-currentDisplacement;
  int displacement2 = (360-currentDisplacement) + initialDisplacement ;

  if(displacement1 < 0)
  {
    displacement1 = -displacement1;
  }

  if(displacement1 < displacement2)
  {
    return displacement1;
  }
  else
  {
    return displacement2;;
  }
}
void Parking::reverseParking(){
  initialDisplacement = sensors -> getAngularDisplacement();
  driver -> setAngle(35);
  driver -> setSpeed(-45);
  //the above 3 statements should be executed before this method is return
  //this is just for the sake of structuring it with ilja later

  if((initialDisplacement - sensors -> getAngularDisplacement() == 45
  || (360 - sensors -> getAngularDisplacement()) + initialDisplacement == 45) && !isReverseParking){
    driver -> setAngle(0);
    delay(50);
    driver -> setAngle(-60);
    isReverseParking = true;
  }
  //two end cases for reverse parking: hitting initial angular displacement
  //or finding an obstacle behind itself

  if(sensors -> getBBDistance() > 0
  && sensors -> getBBDistance() < 10
  && isReverseParking){
    driver -> setAngle(60);
  }

  if((sensors -> getAngularDisplacement() == initialDisplacement) && isReverseParking)
  {
    driver -> stop();
    isReverseParking = false;
  }
}
