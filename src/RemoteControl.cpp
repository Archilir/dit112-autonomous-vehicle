#include <AutonomousCarSystem.h>

// Constructor
RemoteControl::RemoteControl()
{

}

void RemoteControl::begin(Driver* driverRef, Parking* parkingRef)
{
  driver  = driverRef;
  parking = parkingRef;
  timeoutCounter = millis();
  timeoutLock = false;
}

void RemoteControl::listen() {
  if (Serial3.available()) {
    char command = Serial3.read();
    switch (command) {
      case _PARKING:
        if (parking -> isParking())
            parking -> stop();
        else
            parking -> start(parking -> _PARALLEL);
        break;

      case _MANUAL:
        if (parking -> isParking())
            parking -> stop();
        break;

      case _FORWARD: case _REVERSE: case _LEFT: case _RIGHT:
        if (parking -> isParking()) // overrides
          parking -> stop();
        manualControl(command);
      break;

      default:
        if (parking -> isParking())
          parking -> stop();
        else
          driver -> drive(0);
        break;
    }
  } else if (timeoutLock && millis() > (150 + timeoutCounter)) {
      driver -> drive(0);
      driver -> setAngle(0);
      timeoutLock = false;
    }
  }

void RemoteControl::manualControl(char command) {
  switch (command) {
    case _FORWARD:
      driver -> drive(45);
      driver -> setAngle(0);
      driver -> setTurning(false);
      break;

    case _REVERSE:
      driver -> drive(-45);
      driver -> setAngle(0);
      driver -> setTurning(false);
      break;

    case _LEFT:
      driver -> drive(45);
      driver -> setAngle(-75);
      driver -> setTurning(true);
      break;

    case _RIGHT:
      driver -> drive(45);
      driver -> setAngle(75);
      driver -> setTurning(true);
      break;
  }
  timeoutLock = true;
  timeoutCounter = millis();
}
