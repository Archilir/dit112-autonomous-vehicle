#include <Scheduler.h>

void setup()
{
  Serial.begin(9600);
  Serial3.begin(9600);
  sensors.begin(&car);
  driver.begin(&car, &sensors);
  parking.begin(&driver, &sensors);
  remoteControl.begin(&driver, &parking, &sensors);

}

void loop()
{
  sensors.update();
  //sensors.debug();
  remoteControl.listen();
  remoteControl.listenJoystick();
  parking.monitor();
  driver.update();

}
