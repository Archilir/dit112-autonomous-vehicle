#include <Scheduler.h>

void setup()
{
  Serial.begin(9600);
  Serial3.begin(9600);
  sensors.begin(&car);
  driver.begin(&car, &sensors);
  parking.begin(&driver, &sensors);
  avoidance.begin(&driver, &sensors);
  remoteControl.begin(&driver, &parking, &sensors, &avoidance);
}

void loop()
{
  sensors.update();
  //sensors.debug();
  remoteControl.listen();
  //remoteControl.listenJoystick();
  avoidance.monitor();
  parking.monitor();
  driver.update();

}
