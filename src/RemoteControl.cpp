#include <AutonomousCarSystem.h>

void RemoteControl::begin(Driver* driverRef, Parking* parkingRef, Sensors* sensorsRef)
{
  driver  =  driverRef;
  parking = parkingRef;
  sensors = sensorsRef;
}

void RemoteControl::listen() {
  if (Serial3.available()) {
    input = Serial3.read();
    standardScheme(input);
  }
}

void RemoteControl::listenJoystick() {
  if (Serial.available()) {
    switch (Serial.read()) {
      case _LEFT_X_NEGATIVE: driver  -> steer(-pollJoystick()); break;
      case _LEFT_X_POSITIVE: driver  -> steer( pollJoystick()); break;
      case _LEFT_Y_NEGATIVE: driver  -> drive(-pollJoystick()); break;
      case _LEFT_Y_POSITIVE: driver  -> drive( pollJoystick()); break;
      case _LEFT_X_NEUTRAL : driver  -> steer(0);               break;
      case _LEFT_Y_NEUTRAL : driver  -> drive(0);               break;
      case _J_SIREN_ON     : sensors -> sirenOn();              break;
      case _J_SIREN_OFF    : sensors -> sirenOff();             break;
    }
  }
}

int RemoteControl::pollJoystick() {
  while (!Serial.available()) {}
  return Serial.read();
}

void RemoteControl::standardScheme(char input) {
  switch (input) {
    case _SPEED_0   : driver -> setSpeed(  0); break;
    case _SPEED_10  : driver -> setSpeed( 10); break;
    case _SPEED_20  : driver -> setSpeed( 20); break;
    case _SPEED_30  : driver -> setSpeed( 30); break;
    case _SPEED_40  : driver -> setSpeed( 40); break;
    case _SPEED_50  : driver -> setSpeed( 50); break;
    case _SPEED_60  : driver -> setSpeed( 60); break;
    case _SPEED_70  : driver -> setSpeed( 70); break;
    case _SPEED_80  : driver -> setSpeed( 80); break;
    case _SPEED_90  : driver -> setSpeed( 90); break;
    case _SPEED_100 : driver -> setSpeed(100); break;

    case _AUX_1_ON  : break;
    case _AUX_1_OFF : break;
    case _AUX_2_ON  : break;
    case _AUX_2_OFF : break;
    case _AUX_3_ON  : sensors -> sirenOn();  break;
    case _AUX_3_OFF : sensors -> sirenOff(); break;

    // Parking - Triangle
    case _AUX_4_ON  : parking -> initiate(); break;
    case _AUX_4_OFF : parking -> stop();     break;

    case _STOP :
      driver -> disableDriftCorrection();
      driver -> enableTrackingCourse();
      driver -> stop();
      break;

    case _FORWARD: case _BACK:   case _LEFT:    case _RIGHT:
    case _F_LEFT:  case _B_LEFT: case _F_RIGHT: case _B_RIGHT:
      manualControl(input);
      break;
  }
}

void RemoteControl::manualControl(char input) {
  if (parking -> isParking())
    parking -> stop();
  if (driver -> isAutonomous())
    driver -> disableAutonomy();

  switch (input) {
    case _FORWARD:
      driver -> disableTrackingCourse();
      driver -> enableDriftCorrection();
      driver -> driveForward();
      break;

    case _BACK:
      driver -> disableTrackingCourse();
      driver -> enableDriftCorrection();
      driver -> driveBackward();
      break;

    case _LEFT:
      driver -> disableDriftCorrection();
      driver -> enableTrackingCourse();
      driver -> driveLeft();
      break;

    case _F_LEFT:
      driver -> disableDriftCorrection();
      driver -> enableTrackingCourse();
      driver -> driveForwardLeft();
      break;

    case _B_LEFT:
      driver -> disableDriftCorrection();
      driver -> enableTrackingCourse();
      driver -> driveBackwardLeft();
      break;

    case _RIGHT:
      driver -> disableDriftCorrection();
      driver -> enableTrackingCourse();
      driver -> driveRight();
      break;

    case _F_RIGHT:
      driver -> disableDriftCorrection();
      driver -> enableTrackingCourse();
      driver -> driveForwardRight();
      break;

    case _B_RIGHT:
      driver -> disableDriftCorrection();
      driver -> enableTrackingCourse();
      driver -> driveBackwardRight();
      break;

    case _CAMERA_RIGHT:
      break;

    case _CAMERA_LEFT:
      break;
  }
}
