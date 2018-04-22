#include <AutonomousCarSystem.h>

bool isReverseParking = false;
int initialDisplacement;
int previousFront;
int previousBack;
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
    return displacement2;
  }
}
void Parking::reverseParking(){
  initialDisplacement = sensors -> getAngularDisplacement();
  driver -> setAngle(45);
  driver -> setSpeed(-40);
  //the above 3 statements should be executed before this method is return
  //this is just for the sake of structuring it with ilja later

  /*
  * While the car is not aligned for parking, it will attempt to align itself while also maintaining distance
  * from obstacles.
  */

  if(getShortestDisplacement() <= 40 && !isReverseParking){
    if(sensors -> getBRDistance() > 0 && sensors -> getBRDistance() < 10){
      driver -> setAngle(0);
    }
    else{
      driver -> setAngle(45);
    }
  }

  /*
   * After the target displacement is hit, theoretically the car should keep backing up
   * until it is more or less inside the space.
   * After that, it begins turning inside the space and it sets parking status to true.
   */

  if((getShortestDisplacement() > 40)
      && (getShortestDisplacement() < 50)
      && !isReverseParking){

    previousFront = sensors -> getFRDistance();
    previousBack = sensors -> getBRDistance();

    if(previousBack< sensors -> getBRDistance() &&
       previousFront > sensors -> getFRDistance()){
     driver -> setAngle(0);
    }

    else{
     driver -> setAngle(-45);
     isReverseParking = true;
    }
  }

  /*
 * detects obstacles at the back of the car
 * if the car is currently turning to the right, it starts turning to the left
 * if the car is already turning to the left, it just sends it forwards
 */

 long backDistance = sensors -> getBBMedian();

  if(backDistance > 0
  && backDistance < 21
  && isReverseParking){
      driver -> setAngle(45);
      driver -> setSpeed(40);
  }

  /*
   * If the car is aligned to its original displacement, it stops and flicks off the parking switch.
   */

  if(getShortestDisplacement() < 2 && isReverseParking)
  {
    driver -> stop();
    isReverseParking = false;
  }
}
