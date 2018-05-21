#include <AutonomousCarSystem.h>

void Avoidance::begin(Driver* driverReference, Sensors* sensorsReference) {
  driver  = driverReference;
  sensors = sensorsReference;
}
