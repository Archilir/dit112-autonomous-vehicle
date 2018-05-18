#include <AutonomousCarSystem.h>

void Driver::begin(Car* reference, Sensors* sensorRef) {
  car = reference;
  sensors = sensorRef;
  courseValue = sensors -> getAngularDisplacement();
}

void Driver::update() {
  if (isTrackingCourse())
    trackCourse();
  //if (isAligning()) {
  //  align();
  //} else
  if (isDriftCorrecting())
    driftCorrection(courseValue, sensors -> getAngularDisplacement());
}

void Driver::setSpeed(int speed) { speedValue = speed; }
void Driver::setAngle(int angle) { angleValue = angle; }
int  Driver::getSpeed()          { return  speedValue; }
int  Driver::getAngle()          { return  angleValue; }

void Driver::steer(int angle) {
  setAngle(angle);
  steer();
}
void Driver::steer() {
  if (angleValue != car -> getAngle())
    car -> setAngle(angleValue);
}

void Driver::drive(int speed, int angle) {
  setAngle(angle);
  steer();
  drive(speed);
}
void Driver::drive(int speed) {
   setSpeed(speed);
   drive();
}
void Driver::drive() {
  if (car -> getSpeed() == 0 || speedValue < car -> getSpeed()) {
    boost();
  }
  if (speedValue != car -> getSpeed())
    car -> setSpeed(speedValue);
}

void Driver::boost() {
  if (speedValue != 100 && speedValue != -100 && speedValue != 0) {
    if (speedValue > 0)
      car -> setSpeed( 100);
    else
      car -> setSpeed(-100);
    delay(20);
  }
}

void Driver::stop() {
  car -> setAngle(0);
  car -> setSpeed(0);
}

void Driver::driveForward()       { drive( abs(speedValue),   0); }
void Driver::driveBackward()      { drive(-abs(speedValue),   0); }
void Driver::driveLeft()          { drive( abs(speedValue), -90); }
void Driver::driveRight()         { drive( abs(speedValue),  90); }
void Driver::driveForwardLeft()   { drive( abs(speedValue), -75); }
void Driver::driveBackwardLeft()  { drive(-abs(speedValue), -90); }
void Driver::driveForwardRight()  { drive( abs(speedValue),  75); }
void Driver::driveBackwardRight() { drive(-abs(speedValue),  90); }
void Driver::driveCorrectLeft()   { drive( abs(speedValue),  -1); }
void Driver::driveCorrectRight()  { drive( abs(speedValue),   1); }


void Driver::enableAlignment()  { aligning = true;  }
void Driver::disableAlignment() { aligning = false; }
bool Driver::isAligning()       { return aligning;  }

void Driver::align() {
  if (sensors -> passingObstacle()) {
    int side = sensors -> getDistanceMiddleSide() -
               sensors -> getDistanceFrontSide();

    if (side > 0) {
      if (side <=  3)
        driveForwardLeft();
      else
        driveLeft();
    } else
    if (side < 0) {
      if (side >= -3)
        driveForwardRight();
      else
        driveRight();
    } else
        driveForward();

    //if (sensors -> getDistanceFrontSide() > getDistance)
    /*double side = sensors -> getDistanceMiddleSide() -
                  sensors -> getDistanceFrontSide();
    double degree = atan(abs(side) / 7) * 180 / 3.14159265;
    if (side > 0) {
        driftCorrection(courseValue, sensors -> getAngularDisplacement());
    } else
    if (side < 0) {
        driftCorrection(courseValue, sensors -> getAngularDisplacement());

    } else {
        driftCorrection(courseValue, sensors -> getAngularDisplacement());
    }*/
  }



}

void Driver::enableAutonomy() {
  autonomous =  true;
  aligning   =  true;
  manualSpeedValue = speedValue;

  stop();
}

void Driver::disableAutonomy() {
  autonomous = false;
  aligning   = false;
  speedValue = manualSpeedValue;
  stop();
}

bool Driver::isAutonomous()          { return  autonomous; }

void Driver::setCourse(int course)   { courseValue    = course; }
void Driver::enableTrackingCourse()  { trackingCourse =   true; }
void Driver::disableTrackingCourse() { trackingCourse =  false; }
bool Driver::isTrackingCourse()      { return   trackingCourse; }
void Driver::trackCourse() {
  courseValue = sensors -> getAngularDisplacement();
}

void Driver::enableDriftCorrection()  {
  courseValue = sensors -> getUnsyncAngularDisplacement();
  correctingDrift =  true;
}
void Driver::disableDriftCorrection() { correctingDrift = false; }
bool Driver::isDriftCorrecting()      { return  correctingDrift; }
void Driver::driftCorrection(int course, int currentDirection) {
  int diff = (course - currentDirection + 360) % 360;
  if (diff == 0) {
    course = 0;
  }
  else if (diff < 180) {
    if (car -> getSpeed() > 0)
      course = (diff >   4) ?  90 :  1;
    else
      course = (diff >   4) ? -90 : -1;
  }
  else if (diff > 180) {
    if (car -> getSpeed() > 0)
      course = (diff < 356) ? -90 : -1;
    else
      course = (diff < 356) ?  90 :  1;
  }
  steer(course);
  /*Serial.print("Current Direction, Course, Diff:");
  Serial.print('\t');
  Serial.print(currentDirection);
  Serial.print('\t');
  Serial.print(course);
  Serial.print('\t');
  Serial.println(diff);*/
}
