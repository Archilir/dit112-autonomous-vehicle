#include <AutonomousCarSystem.h>

enum {
  _PARKING = 'p',
  _TESTING = 'm'
};

// Constructor
RemoteControl::RemoteControl()
{

}

void RemoteControl::begin(DriveController& newController)
{
  driveController = &newController;
}

void RemoteControl::listen() {
  if (Serial3.available()) {
    switch (Serial3.read()) {
      case _PARKING:
        driveController->reverse();
        break;

      case _TESTING:
        driveController->drive();
        break;

      default:
        driveController->stop();
        break;
    }
  }
}
