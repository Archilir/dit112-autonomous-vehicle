#include <AutonomousCarSystem.h>

Car car;
SensorBridge sensors;
RemoteControl remoteControl;
ParallelParking parking;
DriveController driveController;

void setup()
{
  Serial.begin(9600);
  Serial3.begin(9600);
  sensors.begin(car);
  driveController.begin(car);
  remoteControl.begin(driveController);
  parking.begin(driveController);
}

void loop()
{
  sensors.update();
  driveController.update();
  remoteControl.listen();
  //sensors.debug();
}
