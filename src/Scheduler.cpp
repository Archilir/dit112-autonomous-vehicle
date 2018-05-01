#include <Scheduler.h>

void setup()
{
  Serial.begin(9600);
  Serial3.begin(9600);
  sensors.begin(&car);
  driver.begin(&car, &sensors);
  parking.begin(&driver, &sensors);
  remoteControl.begin(&driver, &parking);
}

void loop()
{
  sensors.update();
  //sensors.obstacleMonitor();
  //sensors.debug();
  remoteControl.listen();
  parking.monitor();
  driver.update();

}
