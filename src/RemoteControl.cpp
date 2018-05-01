#include <AutonomousCarSystem.h>

void RemoteControl::begin(Driver* driverRef, Parking* parkingRef)
{
  driver  =  driverRef;
  parking = parkingRef;
}

void RemoteControl::listen() {
  if (Serial3.available()) {
    input = Serial3.read();
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
      case _AUX_3_ON  : break;
      case _AUX_3_OFF : break;

      // Parking - Triangle
      case _AUX_4_ON  : driver ->  enableAutonomy(); parking -> start(); break;
      case _AUX_4_OFF : driver -> disableAutonomy(); parking -> stop();  break;

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
}

void RemoteControl::manualControl(char input) {
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
  }
}
